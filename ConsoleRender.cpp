#include "ConsoleRender.h"
#include <iostream>

ConsoleRender::ConsoleRender(int width, int height) {
    this->width = width;
    this->height = height;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hConsole == INVALID_HANDLE_VALUE) {
        std::cerr << "Error while getting console handle" << std::endl;
        exit(1);
    }
}

void ConsoleRender::draw(const std::vector<float>& yPositions) {
    clear();
    for (int x = 0; x < width; ++x) {
        int y = static_cast<int>(yPositions[x]);
        if (y >= 0 && y < height) {
            std::cout << "\033[" << (y + 1) << ";" << (x + 1) << "H";
            if (y < height / 2) {
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            } else {
                SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
            }
            std::cout << drawer.getRandomChar(); // Now using direct object
        }
    }
    SetConsoleTextAttribute(hConsole, 7);
    std::cout << std::flush;
}