#ifndef RAINDROP_H
#define RAINDROP_H

#include <vector>
#include <utility>
#include <random>
#include <windows.h>

namespace RainDrop {
    class Program {
    private:
        static std::random_device rd;
        static std::mt19937 randomPosition;
        static HANDLE hConsole;

        static char getAsciiCharacters();
        static int YPositionFields(int yposition, int height);

        static void Initialize(int& width, int& height, std::vector<std::vector<std::pair<char, int>>>& streams);
        static void ColumnUpdate(int width, int height, std::vector<std::vector<std::pair<char, int>>>& streams);

    public:
        static void Main();
    };
}

#endif // RAINDROP_H
#pragma once
