#include "TestStuff.h"

#include <iostream>
using std::cout;
using std::endl;

///////////////////////////////
// global namespace functions
///////////////////////////////

void Print(int nr)
{
    std::cout << "::Print(int) output: " << nr << endl;
}

void PrintTimes(int nr, int nrTimes)
{
    for (int count = 0; count < nrTimes; ++count)
        std::cout << "::PrintTimes(int, int) output: " << nr << endl;
}

//////////////
// Functor
//////////////

void PrintFunctor::operator()(int nr)
{
    std::cout << "MyPrintFunctor::operator()(int) output: " << nr << endl;
}

/////////////////////////
// Test class
/////////////////////////
// 
// initialize static member
int Test::m_NrObjects{};

// member functions

Test::Test() : m_ID(++m_NrObjects)
{
    std::cout << "Test object " << m_ID << " created with value " << m_Value << ".\n";
}

Test::Test(const Test& other) : m_Value(other.m_Value), m_ID(++m_NrObjects)
{
    std::cout << "Copy constructor: test object " << m_ID << " created based on test object " << other.m_ID << ".\n";
}

Test::Test(int value) : m_Value(value), m_ID(++m_NrObjects)
{
    std::cout << "Test object nr " << m_NrObjects << " created with value " << m_Value << ".\n";
}

void Test::SetValue(int newValue)
{
    m_Value = newValue;
}

void Test::IncrementValue()
{
    ++m_Value;
    std::cout << "Test object " << m_ID << " incremented.\n";
}

void Test::DoubleValue()
{
    m_Value *= 2;
    std::cout << "Test object " << m_ID << " doubled.\n";
}

void Test::Print() const
{
    cout << "Test::Print() output for object " << m_ID << " : " << m_Value << endl;
}

void Test::PrintMultiplied(int multiplier) const
{

    cout << "Test::PrintMultiplied(int) output for object " << m_ID << " : " << m_Value * multiplier << endl;
}

void Test::PrintMultipliedTimes(int nrTimes, int multiplier) const
{
    for (int count = 0; count < nrTimes; ++count)
        cout << "Test::PrintMultipliedTimes(int, int) output for object " << m_ID << " : " << m_Value * multiplier << endl;
}

void Test::PrintNrObjects(int nrTimes)
{
    for (int count = 0; count < nrTimes; ++count)
        cout << "static Test::PrintNrObjects(int) output: " << m_NrObjects << " Test objects" << endl;
}

/////////////////////////
// Alternative test class
/////////////////////////
Alternative::Alternative(int value) : m_Value(value)
{}

void Alternative::Print() const
{
    cout << "I am the alternative, zero arguments: " << m_Value << endl;
}

double Alternative::OutputMultiplied(int nrTimes, double multiplier) const
{
    for (int count = 0; count < nrTimes; ++count)
        cout << "I am the alternative " << m_Value * multiplier << endl;

    cout << endl;

    return m_Value * multiplier;
}

void Alternative::IncrementValue()
{
    ++m_Value;
}

void Alternative::DoubleValue()
{
    ++m_Value *= 2;
}
