---
layout: default
title: Digital Rain Project
---

# 💻 Digital Rain in C++

## Introduction

This is my C++ GitHub Pages project powered by **Jekyll**.

The goal of this console application is to recreate the iconic “digital rain” effect from *The Matrix*. It uses the Windows Console API to simulate streams of random characters falling from the top of the screen, with real-time updates to cursor position and text color. The project is organized into multiple files, with a focus on clean structure, modular design, and readable code. I also included a simple test suite to make sure each part of the program works correctly.

---
## 🎥 Demo

<video controls autoplay muted loop playsinline width="720">
  <source src="https://raw.githubusercontent.com/Rayan1605/DigitalRainProject/master/digital_rain_demo.mp4" type="video/mp4">
  Your browser does not support the video tag.
</video> 
## 🧪 Testing Strategy

### Unit Testing

I wrote some basic tests to check that the main functions behave as expected:

- **YPositionFields** – checks if positions wrap correctly at the screen height.
- **getAsciiCharacters** – makes sure the output is a printable character.
- **Initialize** – confirms the screen size is set correctly and columns are initialized.
- **ColumnUpdate** – ensures streams update properly and don’t exceed their limits.

I kept the tests simple and direct, just enough to make sure nothing breaks when I change stuff. Because a lot of the visual output relies on randomness and real-time rendering, most of the testing still had to be done manually.

### Manual Testing

Since this project is visual, I tested it by running it and just watching how it looked. I played around with:

- How the characters flowed — if the motion felt clean and natural.
- Different window sizes — making sure resizing didn’t break it.
- Delay, stream length, and how often new characters show up — to balance CPU usage and how it looks.

---

## 🛠️ How It’s Designed

The first version I had was super flickery. Like, unwatchable levels of flicker. Then I found out about this thing called double buffering in the Windows Console API. Basically, instead of drawing directly to the visible screen, you draw everything to a hidden screen buffer, and then swap it in when it’s ready. This makes it way smoother.

So I had to manually set up the screen size, control cursor movement, and make sure all drawing happened inside bounds. Like, if the console is 120 wide, the furthest I can draw to is position 119, not 120. Otherwise, it’ll throw off the whole frame.

When setting up the streams, I make sure they start above the screen (like -10 or something), so they fall in gradually instead of just popping up in the middle. And the top of each stream is brighter, then it fades — like in the movie.

---

## ⚙️ Algorithm 

This section goes over how the actual effect works. The algorithm is simple at first glance, but there’s a lot of little things you need to get right to make it feel good.

### 1. Setting up the streams

Each stream is a column of characters. Each column is a `std::vector` of pairs. Each pair holds a char and its Y-position. The whole screen is just a list of these columns.

```cpp
std::vector<std::vector<std::pair<char, int>>> streams;
```

During `Initialize()`, I resize the window, set the buffer size, and loop through all columns like this:

```cpp
for (int x = 0; x < width; ++x) {
    int startY = randomPosition() % height;
    int initialLength = (randomPosition() % (height / 3)) + 3;
    for (int i = 0; i < initialLength; ++i) {
        int yPos = YPositionFields(startY - i, height);
        streams[x].push_back({ getAsciiCharacters(), yPos });
    }
}
```

So each column starts with a few characters at different heights, all falling independently.

---

### 2. Updating Streams (Frame by Frame)

Each frame, I loop through all columns and update them. I shuffle the order just for variation.

```cpp
std::shuffle(columns.begin(), columns.end(), randomPosition);
```

For each column:

- I clear the last character from the screen
- I move all characters down by 1
- I sometimes add a new character at the top (not always, for randomness)
- If the stream is too long, I trim it

```cpp
if ((randomPosition() % 100) < 70 && streams[x].size() < maxLength) {
    int newY = YPositionFields(streams[x][0].second - 1, height);
    streams[x].insert(streams[x].begin(), { getAsciiCharacters(), newY });
}
while (streams[x].size() > maxLength) {
    streams[x].pop_back();
}
```

That 70% chance is what makes the rain feel alive. If every column updated every frame, it would look robotic.

---

### 3. Drawing the Frame

Once I’ve updated all columns, I draw them. I use color to separate the stream head from the body.

```cpp
if (i == 0)
    SetConsoleTextAttribute(hConsole, greenColor); // Head (bright)
else if (i == streams[x].size() - 1)
    SetConsoleTextAttribute(hConsole, fadedColor); // Tail (dim)
else
    SetConsoleTextAttribute(hConsole, baseColor); // Body (normal green)
```

After setting the color, I move the cursor and print the character at its Y-position.

The top of the stream is brighter to make it stand out, and the tail fades out so it feels like it disappears smoothly.

---

### 4. Looping the Animation

Everything above runs inside a never-ending loop:

```cpp
while (true) {
    ColumnUpdate(width, height, streams);
    Sleep(50); // delay to control speed
}
```

And yeah, this loop runs forever. `Sleep(50)` gives it a nice pacing — fast enough to be fluid, but slow enough to be readable.

---
## 🧩 Problem-Solving

### 🧨 Runtime Crash: vector subscript out of range

While running the application during one of the animation cycles, I encountered a runtime crash triggered by a standard library assertion:

> **Debug Assertion Failed!**  
> Expression: `vector subscript out of range`  
> File: vector  
> Line: 1916

This error typically occurs when attempting to access an index in a `std::vector` that is outside its valid range — in this case, it was due to referencing `streams[idx][0]` without verifying whether the `streams[idx]` vector was non-empty.

### 🧪 Root Cause Analysis

The problematic line was inside the stream update logic:

```cpp
int newY = YPositionFields(streams[idx][0].second - 1, height);
streams[idx].insert(streams[idx].begin(), { getAsciiCharacters(), newY });
```

This code assumes that `streams[idx]` will always contain at least one element. However, due to the way the animation system trims columns and controls growth probabilistically (with a 70% chance of extension), it's entirely possible for a stream to be emptied out before this code executes.

Since `streams[idx]` was not checked for emptiness before accessing `[0]`, the program attempted to dereference an invalid index, resulting in the crash.

### 🛠️ Resolution

To prevent this, I introduced a simple but critical conditional check to verify that the stream is non-empty before accessing the head of the column:

```cpp
if (!streams[idx].empty() && (randomPosition() % 100) < 70 && streams[idx].size() < maxLength) {
    int newY = YPositionFields(streams[idx][0].second - 1, height);
    streams[idx].insert(streams[idx].begin(), { getAsciiCharacters(), newY });
}
```

This ensures that no vector operation is attempted on an empty container, eliminating the possibility of an out-of-bounds access.

### 🤔 Lessons Learned

- **Safety-first access**: Always check before accessing: Even if your program runs in a controlled way, unexpected things can still happen. Always check the size of a list or vector before trying to access something inside it—especially in systems that run in real time. 
- **Edge cases matter**: Edge cases are important: This bug didn’t happen all the time. It showed up randomly because of rare timing issues. That’s why it’s important to protect your code against unusual situations, even if they don’t seem likely
- **Assertions are helpful**: Use assertions during development: Assertions can stop your program suddenly, but they’re useful when building your code. They help you find wrong assumptions in your logic before they become real problems later.

### ✅ Conclusion

This experience reinforced the importance of defensive programming, particularly when dealing with animation systems that rely on randomness and continuous state updates. A single unchecked assumption—however unlikely—can compromise the stability of the entire application.

By introducing a simple condition, I resolved the issue and made the system significantly more reliable. It’s a small change with a big impact, and a good reminder that resilience often lies in the details.


### 💥 Console Glitch & What Caused It

![glitch](https://github.com/user-attachments/assets/ad958e17-ade7-4b56-beae-f1c024676cf3)


At one point, instead of the smooth Matrix-style rain I was aiming for, the console output completely broke. Characters were flying across the screen, overlapping, and appearing in places they weren’t supposed to. It didn’t look like digital rain — it looked like a visual mess.

At first, I assumed the problem was in the animation logic. I double-checked the update loop, the character generator, and the randomness. But everything seemed fine.

### 💡 What Actually Broke

The real issue wasn’t the logic — it was the console itself.

I was drawing characters **outside the valid screen area**. For example, if the console is 120 columns wide, drawing at column `120` (instead of `0–119`) is out of bounds. That causes the Windows Console to scroll, wrap, or glitch. On top of that, I hadn’t set the window and buffer sizes manually, so the console behavior was unpredictable.

### 🔧 The Fix

To stop that from happening, I explicitly set both the **window size** and the **screen buffer size** so they matched:

```cpp
SMALL_RECT windowSize = { 0, 0, 119, 29 };
SetConsoleWindowInfo(hConsole, TRUE, &windowSize);

COORD bufferSize = { 120, 30 };
SetConsoleScreenBufferSize(hConsole, bufferSize);
```

Once that was in place, everything worked. No more flickering, no more random glitches — just clean, consistent animation.

### ✅ What I Learned

- Always define your console window and buffer sizes — never rely on system defaults.
- The Windows Console won’t stop you from drawing out of bounds — but it will break if you do.
- Even tiny oversights, like writing to column 120 instead of 119, can completely throw off your output.

This bug taught me a lot about how the console works under the hood. Once I fixed it, the visual flow finally looked stable and intentional — exactly what I was going for.



## 🧠 Modern C++ Insight & Reflection

Honestly, I learned a lot just from building this.

- **Vectors and pairs**: Using vectors of `pair<char, int>` was the cleanest way I could think of to track stream characters and their Y-positions together.
- **Randomness**: I used `<random>` and `std::mt19937` instead of `rand()` so the character generation looked less repetitive and felt more “natural”.
- **Multifile project**: Splitting the code into separate header/source files and test files made everything more manageable.
- **System-level stuff**: Working with the Windows Console API was kinda like diving into the guts of how terminal output works. Cursor positioning, screen size, buffer control — all stuff I’d never touched before.

---

## ✅ Conclusion

It taught me how visual feedback is all about detail — like timing, randomness, and subtle effects like brightness or spacing. I had to think about how the console behaves, not just how my logic works. In the end, I think I got it to a point where it actually *feels* like digital rain.

