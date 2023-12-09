#include <iostream> // cout,         wcout,        cin,  wcin
#include <iomanip>  // setprecision, fixed
#include <string>   // string,       wstring
#include <sstream>  // stringstream, wstringstream
#include <tchar.h>  // _T(),         _tmain,       TCHAR

#if defined(_UNICODE) or defined(UNICODE)
    #define tstring std::wstring
    #define tcout std::wcout
    #define tcin std::wcin
    #define tstringstream std::wstringstream
#else
    #define tstring std::string
    #define tcout std::cout
    #define tcin std::cin
    #define tstringstream std::stringstream
#endif

int _tmain(int argc, TCHAR* argv[])
{
    double PI = 3.1415926535897932384626433832795;
    tstringstream print;
    tstring name = _T("John");
    print << _T("Hello ") << name.c_str() << _T("!\n");
    print << _T("PI = ") << std::setprecision(4) << std::fixed << PI << _T("\n");
    tcout << print.str();
}
