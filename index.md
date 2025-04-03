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

## 🛠️ How It’s Designed (Explained Simply)

At first, the animation was very flickery and didn’t look great. I learned about **double buffering** using the Windows Console API, which completely fixed the issue. Double buffering uses two console screen buffers: one that's visible (active), and one in the background (inactive). The program draws the next frame in the inactive buffer and then swaps it in — this prevents flickering and makes the animation smooth.

I also had to set things up using Windows-specific functions. That includes setting the screen size, configuring buffer access, and making sure columns stay within bounds. For example, if the screen is 120 characters wide, you use positions 0–119 (not 0–120) to avoid going out of range.

When creating the columns, I start them above the top of the screen (like at -10) so they fall into view instead of just appearing. For each frame, the program moves the cursor to the right spot, sets the text color, and prints the character. The top of the stream is a brighter green, while the rest are dimmer — just like in the original Matrix effect. After drawing everything, the program swaps the buffers, and the next frame begins.

---


