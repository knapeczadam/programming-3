
//---------------------------
// Includes
//---------------------------
#include "MySimpleString.h"
#include <iostream>

//---------------------------
// Exception Classes
//---------------------------
class StringFullException
{};

//---------------------------
// Initialize statics
//---------------------------
int MySimpleString::m_CountObjects{};

//---------------------------
// Constructor(s) & Destructor
//---------------------------
MySimpleString::MySimpleString() : m_ID(++m_CountObjects)
{
    m_InternalDataPtr = new TCHAR[ARRAYSIZE];

    std::cout << "MySimpleString " << m_ID << " constructed.\n";
}

MySimpleString::MySimpleString(const MySimpleString& other) : m_ID(++m_CountObjects)
{
    m_InternalDataPtr = new TCHAR[ARRAYSIZE];

    for (int index{}; index < ARRAYSIZE; ++index)
        m_InternalDataPtr[index] = other.m_InternalDataPtr[index];

    std::cout << "MySimpleString " << m_ID << " copy constructor fired.\n";
}

MySimpleString& MySimpleString::operator=(const MySimpleString& other)
{
    delete[] m_InternalDataPtr;     // delete the old (already existing) dynamic array

    m_InternalDataPtr = new TCHAR[ARRAYSIZE];

    for (int index{}; index < ARRAYSIZE; ++index)
        m_InternalDataPtr[index] = other.m_InternalDataPtr[index];

    std::cout << "MySimpleString " << m_ID << " copy assignment operator fired.\n";

    return *this;
}

MySimpleString::MySimpleString(MySimpleString&& other) noexcept : m_ID(++m_CountObjects)
{
    m_InternalDataPtr = other.m_InternalDataPtr;
    other.m_InternalDataPtr = nullptr;

    std::cout << "MySimpleString " << m_ID << " move constructor fired.\n";
}

MySimpleString& MySimpleString::operator=(MySimpleString&& other) noexcept
{
    delete[] m_InternalDataPtr;     // delete the old (already existing) dynamic array

    m_InternalDataPtr = other.m_InternalDataPtr;
    other.m_InternalDataPtr = nullptr;

    std::cout << "MySimpleString " << m_ID << " move assignment operator fired.\n";

    return *this;
}

MySimpleString::~MySimpleString()
{
    delete[] m_InternalDataPtr;

    std::cout << "MySimpleString " << m_ID << " destroyed.\n";
}


//---------------------------
// Member functions
//---------------------------
void MySimpleString::Add(TCHAR character) {
    if (m_CurrentPos == ARRAYSIZE - 1) throw StringFullException();
    m_InternalDataPtr[m_CurrentPos++] = character;
}

void MySimpleString::Print() const {
    std::tcout << m_InternalDataPtr << std::endl;
}

