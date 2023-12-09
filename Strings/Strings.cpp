#include <iostream> // std::cout,   std::wcout
#include <string>   // std::string, std::wstring, std::u8string, std::u16string, std::u32string

int main()
{
    // Character array
    //--------------------------------------------------------------------------------
    char c1[] = "Hello";
    char c2[] = {'H', 'e', 'l', 'l', 'o', '\0'};
    char c3[] = {"Hello"};
    char c4[6];
    c4[0] = 'H';
    c4[1] = 'e';
    c4[2] = 'l';
    c4[3] = 'l';
    c4[4] = 'o';
    c4[5] = '\0';

    std::cout << "c1 = " << c1 << '\n';
    std::cout << "c2 = " << c2 << '\n';
    std::cout << "c3 = " << c3 << '\n';
    std::cout << "c4 = " << c4 << '\n';

    // Wide character array
    //--------------------------------------------------------------------------------
    wchar_t wc1[] = L"Hello";
    wchar_t wc2[] = {L'H', L'e', L'l', L'l', L'o', L'\0'};
    wchar_t wc3[] = {L"Hello"};
    wchar_t wc4[6];
    wc4[0] = L'H';
    wc4[1] = L'e';
    wc4[2] = L'l';
    wc4[3] = L'l';
    wc4[4] = L'o';
    wc4[5] = L'\0';

    std::wcout << "wc1 = " << wc1 << '\n';
    std::wcout << "wc2 = " << wc2 << '\n';
    std::wcout << "wc3 = " << wc3 << '\n';
    std::wcout << "wc4 = " << wc4 << '\n';
    
    
    // Character pointer
    //--------------------------------------------------------------------------------
    const char* c5 = "Hello";
    std::cout << "c5 = " << c5 << '\n';

    // Wide character pointer
    //--------------------------------------------------------------------------------
    const wchar_t* wc5 = L"Hello";
    std::wcout << "wc5 = " << wc5 << '\n';
    
    // String
    //--------------------------------------------------------------------------------
    std::string s1 = "Hello";
    std::string s2("Hello");
    std::string s3 = {'H', 'e', 'l', 'l', 'o'};
    std::string s4 = { "Hello" };
    

    std::cout << "s1 = " << s1 << '\n';
    std::cout << "s2 = " << s2 << '\n';
    std::cout << "s3 = " << s3 << '\n';
    std::cout << "s4 = " << s4 << '\n';

    // Wide string
    //--------------------------------------------------------------------------------
    std::wstring ws1 = L"Hello";
    std::wstring ws2(L"Hello");
    std::wstring ws3 = {L'H', L'e', L'l', L'l', L'o'};
    std::wstring ws4 = { L"Hello" };

    std::wcout << "ws1 = " << ws1 << '\n';
    std::wcout << "ws2 = " << ws2 << '\n';
    std::wcout << "ws3 = " << ws3 << '\n';
    std::wcout << "ws4 = " << ws4 << '\n';

    // UTF-8/16/32 character
    //--------------------------------------------------------------------------------
    const char8_t* c6 = u8"Hello";
    const char16_t* c7 = u"Hello";
    const char32_t* c8 = U"Hello";

    // UTF-8/16/32 string
    std::u8string s5 = u8"Hello";
    std::u16string s6 = u"Hello";
    std::u32string s7 = U"Hello";
}
