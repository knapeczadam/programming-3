#include <iostream> // std::cout, std::wcout
#include <tchar.h>  // _T,        _tcslen,   _tmain

#if defined(UNICODE) or defined(_UNICODE)
#define tcout std::wcout
#else
#define tcout std::cout
#endif

int _tmain(int argc, TCHAR* argv[])
{
    TCHAR cstr[] = _T("Hello, World!");
    tcout << _T("Length of string \"") << cstr << _T("\" is ") << _tcslen(cstr) << _T('\n');
    tcout << _T("Size of string \"") << cstr << _T("\" is ") << sizeof(cstr) << _T('\n');
}
