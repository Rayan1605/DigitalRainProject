#ifndef TEST_H
#define TEST_H
#include <iostream> // cout
void SomeVectors();
//void DemoAMemoryBug();
void Strings();
void SomeAlorithms();
void DemoForEach();
void PrintFunction(int);

class PrintClass {
private:

public:
	void operator()(int e) { std::cout << e << " "; }
};
#endif