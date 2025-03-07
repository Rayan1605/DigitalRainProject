
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric> // For std::accumulate
#include "Test.h"

void SomeVectors() {
	std::cout << "Instantiate Some Vectors" << std::endl;

	std::vector<std::string> v1(10);
	std::vector<int> v2;

	v2.push_back(3);
	v2.push_back(5);
	v2.push_back(7);
	v2.push_back(8);

	std::vector<std::string> v9{ "Python", "C", "C++" };



	v1.at(2) = "Works";
	v1.at(1) = "second";

	v1.at(7) = "Hi!";

	for (auto const &i : v1) { // The auto is telling the complier to figure out the variable, the const is maing it read only so you can't change the value and
		//the & is making sure it does not copy which can save memory
		std::cout << i << std::endl;
	}
}

void DemoAMemoryBug(){
	std::vector<int> v;

	v[5] = 2.71;

}

void Strings() {
	std::cout << "Instantiate Some Strings" << std::endl;

	std::vector<std::string> v1;

	v1.push_back("Python");
	v1.push_back("C++");
	v1.push_back("Java");
	v1.push_back("P");
	v1.push_back("Python");
	std::vector<std::string> v2(v1);

	std::cout << "Printing the First vector \n" << std::endl;


	for (auto const& i : v1) {
		std::cout << i << std::endl;
	}

	std::cout << "Printing the Second\n" << std::endl;


	for (auto const& i : v2) {
		std::cout << i << std::endl;
	}

	std::cout << "Printing the Second vector again\n" << std::endl;

  
	for (int i = 0; i < v2.size(); i++) {
		if (i == 0) {
			v2.at(0) = "C";
		}
		if (i == 1) {
			v2.at(1) = "Java";
		}
		if (i == 2) {
			v2.at(2) = "Python";
		}
		if (i == 3) {
			v2.at(3) = "Javascript";
		}
		if (i == 4) {
			v2.at(4) = "C++";
		}
	}

	for (auto const& i : v2) {
		std::cout << i << std::endl;
	}


}

void SomeAlorithms() {

	std::vector<int> v{ 1, 9, 4, 5, 6, 2, 0, 7, 3, 8 };

	for (auto const& r : v) {
		std::cout << r << " ";
	}
	std::cout << std::endl << std::endl;

	std::sort(v.begin(), v.end());
	
	for (auto const& r : v) {
		std::cout << r << " ";
	}
	std::cout << std::endl << std::endl;

	std::reverse(v.begin(), v.end());
	
	for (auto const& r : v) {
		std::cout << r << " ";
	}
	std::cout << std::endl << std::endl;
	int zero_count = std::count(v.begin(), v.end(), 0);
	std::cout << "Number of zeros: " << zero_count << std::endl << std::endl;

	auto max_element = std::max_element(v.begin(), v.end());
	if (max_element != v.end()) {
		std::cout << "This is the maximum element: " << *max_element << std::endl;
	}

	int sum = std::accumulate(v.begin(), v.end(), 0);
	std::cout << "Sum of elements: " << sum << std::endl << std::endl;






}


void DemoForEach() {

	std::vector<int> v{ 1,2,3,4,5 };

	std::cout << "1: Print a vector using for_each algorithm with a lambda" << std::endl;

	std::for_each(v.begin(), v.end(), []( int& x) // The [] means that it will only use the numbers inside the scope
		{ 
		std::cout << x << " ";  
		x = 9;
		std::cout << x << " " << std::endl;

		});

	std::cout << "2: Print a vector using for_each algorithm with a function" << std::endl;

	auto PrintLambda = [](const int& i) 
		{
			std::cout << i << " ";

		}; 

	std::for_each(v.begin(), v.end(), PrintLambda);




	std::cout << "3: Print a vector using for_each algorithm with a function" << std::endl;
	std::for_each(v.begin(), v.end(), PrintFunction);



	std::cout << "3: Print a vector using for_each algorithm with a function (functor)" << std::endl;
	PrintClass printobject;
	std::for_each(v.begin(), v.end(), printobject);



}

void PrintFunction(int e) {
	std::cout << e << " ";
}