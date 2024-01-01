
// StringDemo.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cstring>

int main()
{
    char cstring_1[] { 'K', 'e', 'v', 'i', 'n', '\0' };
    char cstring_2[] { "Kevin" };

    std::cout << std::strlen(cstring_1) << std::endl;
    std::cout << std::strlen(cstring_2);
}
