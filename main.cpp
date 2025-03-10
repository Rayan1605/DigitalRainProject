#include <iostream>
#include <windows.h>
int main() {
 HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    if (console== INVALID_HANDLE_VALUE)
    {
        std::cerr << "Error while getting console handle" << std::endl;
        return 1;
    }

    SetConsoleTextAttribute(console, FOREGROUND_RED | FOREGROUND_INTENSITY);
    std::cout<<"Hello, "<<std::endl;

    SetConsoleTextAttribute(console, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    std::cout<<"World!"<<std::endl;

    SetConsoleTextAttribute(console, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    std::cout<<"This is Blue!"<<std::endl;

    return 0;
}

// TIP See CLion help at <a
// href="https://www.jetbrains.com/help/clion/">jetbrains.com/help/clion/</a>.
//  Also, you can try interactive lessons for CLion by selecting
//  'Help | Learn IDE Features' from the main menu.