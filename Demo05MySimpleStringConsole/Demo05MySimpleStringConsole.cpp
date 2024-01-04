// RValueReferences.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "MySimpleString.h"

MySimpleString DressString(const std::tstring& input, char character, int repeat) // the function DressString() is an rvalue (xvalue) expression 
{
    MySimpleString temp{};

    for (int count{}; count < repeat; ++count) temp.Add(character);
    for (TCHAR character : input) temp.Add(character);
    for (int count{}; count < repeat; ++count) temp.Add(character);
    temp.Add(_T('\0'));                                             // add the null terminator

    return temp;
}

int main()
{
    // MySimpleString demo: return values.

    //MySimpleString&         result{ DressString(_T("Kevin"), _T('_'), 3) };               // 1. lvalue reference, won't compile
    //MySimpleString&&        result{ DressString(_T("Kevin"), _T('_'), 3) };               // 2. rvalue reference, uses a hidden variable
    //const MySimpleString&   result{ DressString(_T("Kevin"), _T('_'), 3) };               // 3. lvalue reference to const, uses a hidden variable
    MySimpleString          result{ DressString(_T("Kevin"), _T('_'), 3) };                 // 4. make a new variable via copy or move

    result.Print();
}