// Demo2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <tchar.h>

#include <iostream>
#include <iomanip>                      // for IO manipulators
#include <string>
#include <sstream>
using namespace std;

#ifdef _UNICODE	                        // custom tchar defines
#define tstring wstring
#define tcout wcout
#define tstringstream wstringstream
#else
#define tstring string
#define tcout cout
#define tstringstream stringstream
#endif		

int _tmain(int argc, TCHAR* argv[])
{
    double PI{ 3.141592654 };
    tstringstream printBuffer;
    tstring name{ _T("Kevin") };

    printBuffer << _T("The name ");
    printBuffer << name.c_str();
    printBuffer << _T(" occurs ");
    printBuffer << setw(5) << 23;
    printBuffer << _T(" times in this document!") << endl << endl;
    printBuffer << _T("PI 4 digits after the comma is: ");
    printBuffer << setprecision(4) << fixed << PI;
    printBuffer << endl << endl;

    tcout << printBuffer.str() << endl;

    cin.get();
    return 0;
}