#include <iostream>
#include <tchar.h>

#if defined(UNICODE) or defined(_UNICODE)
#define tcout std::wcout
#define tcin std::wcin
#else
#define tcout std::cout
#define tcin std::cin
#endif

int _tmain(int argc, TCHAR* argv[])
{
    for (int i = 0; i < argc; ++i)
    {
        tcout << argv[i] << _T('\n');
    }
    
    tcin.get();
    return 0;
}
