---
layout: default
title: Digital Rain Project
---

# 💻 Digital Rain in C++

## Introduction

This project is a C++ console-based simulation of the iconic “digital rain” effect from *The Matrix*. It uses the Windows Console API for low-level control over cursor positioning and text rendering, and applies structured programming techniques to maintain modularity and performance. This write-up offers a deep dive into the architecture, logic, and modern C++ practices used throughout the code.

---

## 🧪 Testing Strategy

### Unit Testing

Several core functions were unit-tested to ensure expected behavior:

#### `YPositionFields(int y, int height)`

Wraps the y-coordinate to ensure it stays within bounds:

```cpp
int Program::YPositionFields(int y, int height) {
    return (y + height) % height;
}
```

**Purpose**: This ensures negative positions or values that exceed the screen height wrap around, keeping character motion seamless.

#### `getAsciiCharacters()`

Generates a printable character with weighted randomness:

```cpp
char Program::getAsciiCharacters() {
    int t = randomPosition() % 10;
    if (t <= 2) return '0' + (randomPosition() % 10);        // digits
    else if (t <= 4) return 'a' + (randomPosition() % 26);   // lowercase
    else if (t <= 6) return 'A' + (randomPosition() % 26);   // uppercase
    else return (randomPosition() % (255 - 32) + 32);        // any printable char
}
```

This design favors a blend of digits and letters for a classic "Matrix" aesthetic, while occasionally introducing random printable characters for visual variation.

#### `Initialize()`

Initializes the screen size and column data:

```cpp
void Program::Initialize(int& width, int& height, std::vector<std::vector<std::pair<char, int>>>& streams) {
    // Console setup
    // Determine screen size
    // Resize stream vector
    // Initialize random characters
}
```

Checks ensure the correct screen size is used and every column is properly seeded with at least one character stream.

#### `ColumnUpdate()`

Manages the falling animation logic for each stream:

```cpp
void Program::ColumnUpdate(int width, int height, std::vector<std::vector<std::pair<char, int>>>& streams) {
    // Clear last char
    // Move characters down
    // Insert new character at top
    // Trim streams if necessary
    // Set colors and print
}
```

Unit tests validate that characters wrap, columns don’t exceed the maximum height, and stream behavior remains consistent.

---

## 🎮 How It’s Designed

### Double Buffering with Windows API

To eliminate flickering, two screen buffers are created and swapped every frame:

```cpp
HANDLE hConsole = CreateConsoleScreenBuffer(...);
SetConsoleActiveScreenBuffer(hConsole);
```

This technique ensures that only fully drawn frames are displayed.

### Console Setup

Screen dimensions are set to:

```cpp
SMALL_RECT windowSize = { 0, 0, 119, 29 };
COORD bufferSize = { 120, 30 };
SetConsoleWindowInfo(hConsole, TRUE, &windowSize);
SetConsoleScreenBufferSize(hConsole, bufferSize);
```

All cursor positions and characters are drawn relative to this defined space.

---

## ⚙️ Algorithm Breakdown

### 1. Column Structure

Each column is a `std::vector<std::pair<char, int>>`, storing characters and their current Y positions.

```cpp
std::vector<std::vector<std::pair<char, int>>> streams;
```

Each column updates independently, enabling natural, non-repetitive visual flow.

---

### 2. Column Behavior

- Characters are shifted downward.
- New characters are added at the top with a probability.
- The column wraps around using `YPositionFields()`.
- Streams are trimmed if they exceed the height limit.

```cpp
if ((randomPosition() % 100) < 70 && streams[x].size() < maxLength) {
    int newY = YPositionFields(streams[x][0].second - 1, height);
    streams[x].insert(streams[x].begin(), { getAsciiCharacters(), newY });
}
```

---

### 3. Drawing and Color Logic

Characters are colored to indicate motion:

```cpp
if (i == 0) SetConsoleTextAttribute(hConsole, greenColor); // Head
else if (i == streams[x].size() - 1) SetConsoleTextAttribute(hConsole, fadedColor); // Tail
else SetConsoleTextAttribute(hConsole, baseColor); // Body
```

A mix of intensities gives the illusion of glowing, fading, and flowing.

---

### 4. Continuous Animation

The main loop runs indefinitely, updating columns and drawing frames:

```cpp
while (true) {
    ColumnUpdate(width, height, streams);
    Sleep(50); // Frame delay
}
```

By using `Sleep()`, the animation speed is regulated while keeping CPU usage low.

---

## 🧠 Modern C++ Insight & Reflection

This project allowed me to apply modern C++ in a visual, interactive way. Key takeaways:

- **STL Usage**: `std::vector` and `std::pair` offered flexible ways to manage dynamic character data per column.
- **Randomization**: Leveraging `<random>` and `std::mt19937` gave more control and consistency over randomness than `rand()`.
- **Code Organization**: Splitting logic into `RainDrop.h`, `RainDrop.cpp`, and `TestRainDrop.h/cpp` kept things clean and testable.
- **Low-Level Console Control**: Working with the Windows API introduced new challenges, from buffer swapping to cursor movement and color control.

---

## ✅ Conclusion

This wasn’t just a fun effect to recreate — it was an opportunity to understand how animation, randomness, memory, and structured programming all connect in a console environment. From testing logic and wraparound math to buffer flicker-fighting and weighted randomness, every part played a role in getting the look and feel just right.


