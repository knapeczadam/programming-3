#include <iostream> // std::cout, std::wcout
#include <tchar.h> // _T(), TCHAR, _tmain()

#if defined(UNICODE) or defined(_UNICODE)
    #define tcout std::wcout
    #define tcin std::wcin
#else
    #define tcout std::cout
    #define tcin std::cin
#endif

int _tmain(int argc, TCHAR* argv[])
{
#if defined(UNICODE) or defined(_UNICODE)
    std::wcout << L"int wmain(int argc, wchar_t* argv[])" << '\n';
#else
    std::cout << "int main(int argc, char* argv[])" << '\n';
#endif
    tcout << _T("size of TCHAR: ") << sizeof(TCHAR);
    
    tcin.get();
    return 0;
}
