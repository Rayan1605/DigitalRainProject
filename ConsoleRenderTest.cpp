#include <iostream>
#include <vector>
#include "ConsoleRender.h"
#include "ConsoleRenderTest.h"

void runTests() {
    TestConsoleRenderConstructor();
    TestConsoleRenderDraw();
    TestConsoleRenderwithInvalid();

    std::cout << "All tests passed!" << std::endl;
}

void TestConsoleRenderConstructor() {
    ConsoleRender consoleRender(10, 20);
    std::cout << "TestConsoleRenderConstructor passed!" << std::endl;
}

void TestConsoleRenderDraw() {
    ConsoleRender consoleRender(10, 20);
    std::vector<float> yPositions(10, 10);
    consoleRender.draw(yPositions);
    std::cout << "TestConsoleRenderDraw passed!" << std::endl;
}