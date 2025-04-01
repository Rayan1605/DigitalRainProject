#include "RainDrop.h"
#include <iostream>
#include <vector>
#include <random>
#include <numeric>
#include <algorithm>
#include <windows.h>

namespace RainDrop {
    std::random_device Program::rd;
    std::mt19937 Program::randomPosition(Program::rd());
    HANDLE Program::hConsole = nullptr;

    const WORD baseColor = FOREGROUND_GREEN;
    const WORD greenColor = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
    const WORD fadedColor = FOREGROUND_GREEN;

    char Program::getAsciiCharacters() {
        int t = randomPosition() % 10;
        if (t <= 2) return static_cast<char>('0' + (randomPosition() % 10));
        else if (t <= 4) return static_cast<char>('a' + (randomPosition() % 26));
        else if (t <= 6) return static_cast<char>('A' + (randomPosition() % 26));
        else return static_cast<char>(randomPosition() % (255 - 32) + 32);
    }

    int Program::YPositionFields(int yposition, int height) {
        return (yposition + height) % height;
    }

    void Program::Initialize(int& width, int& height, std::vector<std::vector<std::pair<char, int>>>& streams) {
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        if (hConsole == INVALID_HANDLE_VALUE) {
            std::cout << "Error: Could not get console handle!" << std::endl;
            return;
        }

        SMALL_RECT windowSize = { 0, 0, 119, 29 };
        SetConsoleWindowInfo(hConsole, TRUE, &windowSize);
        COORD bufferSize = { 120, 30 };
        SetConsoleScreenBufferSize(hConsole, bufferSize);

        if (!GetConsoleScreenBufferInfo(hConsole, &csbi)) {
            width = 120;
            height = 30;
        }
        else {
            width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
            height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
        }

        streams.resize(width);
        system("cls");

        for (int x = 0; x < width; ++x) {
            int startY = randomPosition() % height;
            int initialLength = (randomPosition() % (height / 3)) + 3;
            streams[x].clear();
            for (int i = 0; i < initialLength; ++i) {
                int yPos = YPositionFields(startY - i, height);
                streams[x].push_back({ getAsciiCharacters(), yPos });
            }
        }
    }

    void Program::ColumnUpdate(int width, int height, std::vector<std::vector<std::pair<char, int>>>& streams) {
        COORD pos;
        const size_t maxLength = height / 4;

        std::vector<int> columns(width);
        std::iota(columns.begin(), columns.end(), 0);
        std::shuffle(columns.begin(), columns.end(), randomPosition);

        for (int idx : columns) {
            if (streams[idx].empty()) continue;

            pos = { static_cast<SHORT>(idx), static_cast<SHORT>(streams[idx].back().second) };
            SetConsoleCursorPosition(hConsole, pos);
            std::cout << ' ';

            for (auto& charPos : streams[idx]) {
                charPos.second = YPositionFields(charPos.second + 1, height);
            }

            if ((randomPosition() % 100) < 70 && streams[idx].size() < maxLength) {
                int newY = YPositionFields(streams[idx][0].second - 1, height);
                streams[idx].insert(streams[idx].begin(), { getAsciiCharacters(), newY });
            }

            while (streams[idx].size() > maxLength) {
                streams[idx].pop_back();
            }

            for (size_t i = 0; i < streams[idx].size(); ++i) {
                int y = streams[idx][i].second;
                pos = { static_cast<SHORT>(idx), static_cast<SHORT>(y) };
                SetConsoleCursorPosition(hConsole, pos);

                if (i == 0) {
                    SetConsoleTextAttribute(hConsole, greenColor);
                }
                else if (i == streams[idx].size() - 1) {
                    SetConsoleTextAttribute(hConsole, fadedColor);
                }
                else {
                    SetConsoleTextAttribute(hConsole, baseColor);
                }

                std::cout << streams[idx][i].first;
            }
        }
    }

    void Program::Main() {
        hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        if (hConsole == INVALID_HANDLE_VALUE) {
            std::cout << "Error: Could not get console handle!" << std::endl;
            return;
        }
        SetConsoleTextAttribute(hConsole, baseColor);

        CONSOLE_CURSOR_INFO cursorInfo;
        GetConsoleCursorInfo(hConsole, &cursorInfo);
        cursorInfo.bVisible = false;
        SetConsoleCursorInfo(hConsole, &cursorInfo);

        int width, height;
        std::vector<std::vector<std::pair<char, int>>> streams;
        Initialize(width, height, streams);

        while (true) {
            ColumnUpdate(width, height, streams);
            Sleep(50);
        }
    }
}