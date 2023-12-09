#include <iostream> // std::cout, std::wcout
#include <tchar.h>  // _T,        _tcslen,   _tmain

#if defined(UNICODE) or defined(_UNICODE)
#define tcout std::wcout
#define tcin std::wcin
#else
#define tcout std::cout
#define tcin std::cin
#endif

size_t length(const TCHAR* str)
{
    size_t len = 0;
    while (str[len] != '\0') ++len;
    return len;
}

int _tmain(int argc, TCHAR* argv[])
{
    TCHAR cstr[] = _T("Hello, World!");
    tcout << _T("Length of string \"") << cstr << _T("\" is ") << _tcslen(cstr) << _T('\n');
    tcout << _T("Size of string \"") << cstr << _T("\" is ") << sizeof(cstr) << _T('\n');
    tcout << _T("Length of string \"") << cstr << _T("\" is ") << length(cstr) << _T('\n');
    
    tcin.get();
    return 0;
}
