---
layout: default
title: Digital Rain Project
---

# 💻 Digital Rain in C++

## Introduction

This is my C++ GitHub Pages project powered by **Jekyll**.

The goal of this console application is to recreate the iconic “digital rain” effect from *The Matrix*. It uses the Windows Console API to simulate streams of random characters falling from the top of the screen, with real-time updates to cursor position and text color. The project is organized into multiple files, with a focus on clean structure, modular design, and readable code. I also included a simple test suite to make sure each part of the program works correctly.

---

## 🧪 Testing Strategy

### Unit Testing

I wrote some basic tests to check that the main functions behave as expected:

- **YPositionFields** – checks if positions wrap correctly at the screen height.
- **getAsciiCharacters** – makes sure the output is a printable character.
- **Initialize** – confirms the screen size is set correctly and columns are initialized.
- **ColumnUpdate** – ensures streams update properly and don’t exceed their limits.

The tests cover the essentials. Since randomness and visuals are a big part of the project, I also relied on manual testing.

### Manual Testing

Since this project is visual, I tested it by running it directly and observing the output. I focused on:

- How smooth and natural the falling effect looked.
- Running the program in different console sizes to check formatting.
- Adjusting delay, character spacing, and update logic to balance performance and visual quality.

---

## 🛠️ How It’s Designed

At first, the animation was very flickery and didn’t look great. I learned about **double buffering** using the Windows Console API, which completely fixed the issue. Double buffering uses two console screen buffers: one that's visible (active), and one in the background (inactive). The program draws the next frame in the inactive buffer and then swaps it in — this prevents flickering and makes the animation smooth.

I also had to set things up using Windows-specific functions. That includes setting the screen size, configuring buffer access, and making sure columns stay within bounds. For example, if the screen is 120 characters wide, you use positions 0–119 (not 0–120) to avoid going out of range.

When creating the columns, I start them above the top of the screen (like at -10) so they fall into view instead of just appearing. For each frame, the program moves the cursor to the right spot, sets the text color, and prints the character. The top of the stream is a brighter green, while the rest are dimmer — just like in the original Matrix effect. After drawing everything, the program swaps the buffers, and the next frame begins.

---

## ⚙️ Algorithm

The digital rain effect is created using a simple but well-structured update loop that simulates falling characters. Each column is treated as an independent vertical stream, made up of a list of characters with assigned Y-positions. By updating these columns frame by frame and drawing them to the console using the Windows API, the animation achieves a natural, smooth rain-like motion.

### 1. Initialization

At the start, the program resizes the console window and buffer using Windows-specific functions. Two screen buffers are created — one for display and one for drawing — enabling double buffering to eliminate flickering. Columns are then initialized with random lengths and starting positions to avoid uniform movement. Each column is stored as a vector of character and position pairs:

```cpp
std::vector<std::vector<std::pair<char, int>>> streams;
```

This structure allows each column to be updated independently, giving the overall effect a randomized, dynamic appearance.

### 2. Column Representation and Movement

Each column acts as its own stream, where:

- The top of the column holds the newest character.
- Characters are moved down one position every frame.
- When a character reaches the bottom, it wraps back to the top using `YPositionFields()`.
- New characters are added at the top with a certain probability. This randomness helps avoid repetitive patterns.
- If a column becomes too long (beyond `height / 4`), excess characters are removed to maintain performance and visual consistency.

---

### 3. Drawing and Updating the Frame

For each frame:

- The last character in the column is cleared from the console.
- All character positions are updated.
- A new character may be inserted at the top.
- Console colors are set: the leading character is bright green, and the rest fade to darker shades.

The updated positions are then drawn using cursor movement and character output functions. After the entire frame is drawn, the screen buffers are swapped to show the new frame instantly, creating a clean, flicker-free visual.

---

### 4. Continuous Animation Loop

The main loop runs continuously, calling the update and draw logic for each column, followed by a short delay:

```cpp
while (true) {
    ColumnUpdate(width, height, streams);
    Sleep(50); // Control animation speed
}
```

Because each column updates independently, the animation feels more organic and less predictable. The combination of position shifting, randomness, and double-buffered rendering results in a visually smooth and engaging digital rain effect.

---

## 🧠 Modern C++ Insight & Reflection

This project gave me a solid chance to explore and apply some key features of modern C++. One of the main things I focused on was writing code that’s clean, modular, and easy to maintain — even in a visual, console-based project like this.

Here are a few things I made good use of:

- **STL Containers** – I used `std::vector` and `std::pair` heavily to manage columns and character positions in a flexible and dynamic way.
- **Random Number Generation** – I worked with the `<random>` library and `std::mt19937` to create more natural and varied behavior in the character streams.
- **Modular File Structure** – The project is broken into multiple files for clarity — separating testing, logic, and declarations helped keep things readable and organized.
- **Windows API Integration** – I learned how to directly interact with the console using the Windows API — for cursor movement, color output, and double buffering — which was new territory for me.

Overall, this was a hands-on way to apply modern C++ techniques while learning how to build a low-level, visually-driven project. It helped me understand not just how to write code, but how to structure and maintain it in a clean and scalable way.


