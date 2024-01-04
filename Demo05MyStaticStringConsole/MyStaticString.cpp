
//---------------------------
// Includes
//---------------------------
#include "MyStaticString.h"
#include <iostream>

//---------------------------
// Exception Classes
//---------------------------
class StringFullException
{};

//---------------------------
// Initialize statics
//---------------------------
int MyStaticString::m_CountObjects{};

//---------------------------
// Constructor(s) & Destructor
//---------------------------
MyStaticString::MyStaticString() : m_ID(++m_CountObjects)
{
    std::cout << "MyStaticString " << m_ID << " constructed.\n";
}

MyStaticString::MyStaticString(const MyStaticString& other) : m_ID(++m_CountObjects)
{
    for (int index{}; index < ARRAYSIZE; ++index)
        m_InternalData[index] = other.m_InternalData[index];

    std::cout << "MyStaticString " << m_ID << " copy constructor fired.\n";
}

MyStaticString::~MyStaticString()
{
    std::cout << "MyStaticString " << m_ID << " destroyed.\n";
}

MyStaticString& MyStaticString::operator=(const MyStaticString& other)
{
    for (int index{}; index < ARRAYSIZE; ++index)
        m_InternalData[index] = other.m_InternalData[index];

    std::cout << "MyStaticString " << m_ID << " copy assignment operator fired.\n";

    return *this;
}

//---------------------------
// Member functions
//---------------------------
void MyStaticString::Add(TCHAR character) {
    if (m_CurrentPos == ARRAYSIZE - 1) throw StringFullException();

    m_InternalData[m_CurrentPos++] = character;
}

void MyStaticString::Print() const {
    std::tcout << m_InternalData << std::endl;
}

