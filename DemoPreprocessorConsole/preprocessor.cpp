// preprocessor.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include "Z.h"

#define DOUBLE(something) ((something)+(something))
#define PI 3.14

#ifdef NDEBUG
#define ASSERT(cont) 
#else
#define ASSERT(cond) assert_helper(cond, __LINE__)
void assert_helper(bool cond, int line) {
	if (!cond) {
		std::cout << "Assertion failed in file: " << __FILE__ << "( line " << line << ")\n";
	}
}
#endif

#define COMPILE_TIME_ASSERT(condition) extern int myFakeArray[condition]

#define MERGE(a, b) a##b

int main()
{
	MERGE(assert_, helper)(false, 420);
	COMPILE_TIME_ASSERT(010 == 8);
#line 500
	ASSERT((2 + 2) == 6);
	std::cout << PI << std::endl;
	std::cout << DOUBLE(7)*2 << std::endl;
	std::cout << DOUBLE(PI) << std::endl;
	int i{ 4 };
	std::cout << DOUBLE(++i) << std::endl;

}


COMPILE_TIME_ASSERT(011 == 9);

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
