
// RValueReferences.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "MyStaticString.h"

MyStaticString DressString(const std::tstring& input, TCHAR character, int repeat) // the function DressString() is an rvalue (xvalue) expression 
{
    MyStaticString temp{};

    for (int count{}; count < repeat; ++count) temp.Add(character);
    for (TCHAR character : input) temp.Add(character);
    for (int count{}; count < repeat; ++count) temp.Add(character);

    return temp;
}

int main()
{
    // MyStaticString demo: return values.

    //MyStaticString&         result{ DressString(_T("Kevin"), _T('_'), 3) };               // 1. lvalue reference, won't compile
    MyStaticString&&        result{ DressString(_T("Kevin"), _T('_'), 3) };               // 2. rvalue reference, uses a hidden variable
    //const MyStaticString&   result{ DressString(_T("Kevin"), _T('_'), 3) };               // 3. lvalue reference to const, uses a hidden variable
    //MyStaticString          result{ DressString(_T("Kevin"), _T('_'), 3) };                 // 4. make a new variable via copy or move

    result.Print();
}
