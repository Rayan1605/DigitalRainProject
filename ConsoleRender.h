#ifndef CONSOLE_RENDERER_H
#define CONSOLE_RENDERER_H

#include <vector>
#include <windows.h>
#include "Drawing.h" // Include since we're directly using the class

class ConsoleRender {
public:
    ConsoleRender(int width, int height);
    void draw(const std::vector<float>& yPositions);
    void clear();

private:
    int width;
    int height;
    HANDLE hConsole;
    Drawing drawer; // Directly store object, no pointer needed
};

#endif // CONSOLE_RENDERER_H