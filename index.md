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

## 🧠 Modern C++ Insight & Reflection

Honestly, I learned a lot just from building this.

- **Vectors and pairs**: Using vectors of `pair<char, int>` was the cleanest way I could think of to track stream characters and their Y-positions together.
- **Randomness**: I used `<random>` and `std::mt19937` instead of `rand()` so the character generation looked less repetitive and felt more “natural”.
- **Multifile project**: Splitting the code into separate header/source files and test files made everything more manageable.
- **System-level stuff**: Working with the Windows Console API was kinda like diving into the guts of how terminal output works. Cursor positioning, screen size, buffer control — all stuff I’d never touched before.

---

## ✅ Conclusion

It taught me how visual feedback is all about detail — like timing, randomness, and subtle effects like brightness or spacing. I had to think about how the console behaves, not just how my logic works. In the end, I think I got it to a point where it actually *feels* like digital rain.

