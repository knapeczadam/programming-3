
// RValueReferences.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

struct Point
{
    int x, y;
};

void Draw(Point& location)
{
    std::cout << "Point {" << location.x << ", " << location.y << "} using lvalue reference\n";
}

void Draw(const Point& location)
{
    std::cout << "Point {" << location.x << ", " << location.y << "} using const lvalue reference\n";
}

void Draw(Point&& location)
{
    std::cout << "Point {" << location.x << ", " << location.y << "} using rvalue reference\n";
}

void Draw(const Point&& location)
{
    std::cout << "Point {" << location.x << ", " << location.y << "} using const rvalue reference\n";
}

/*
void Draw(Point location)
{
    std::cout << "Point {" << location.x << ", " << location.y << "} using by value\n";
}
*/

template <typename Type>
void Draw(Type&& location) // universal reference, aka. forwarding reference
{
    std::cout << "Point {" << location.x << ", " << location.y << "} using universal reference\n";
}

void PrintNumber(int&& number)
{
    std::cout << "The number is " << number << std::endl;
}

int main()
{
    //// Point demo
    Point pointVar{ 10, 10 };
    
    Draw(pointVar);
    Draw(Point{ 50, 50 });
}
