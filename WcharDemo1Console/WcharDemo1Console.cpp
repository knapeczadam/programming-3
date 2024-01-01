
// Demo1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

/*
#include <iostream>
#include <string>

int main(int argc, char* argv[])
{
    std::cout << "\n\"A veritable smörgåsbord of system functions\"\n\n";
    std::cout << "The tetragrammaton is: יהוה" << std::endl;
    std::cout << "15€" << std::endl;
}
*/

// https://stackoverflow.com/questions/44052505/i-want-to-print-in-hebrew-from-right-to-left-to-the-console 
#include <iostream>
#include <io.h>
#include <fcntl.h>
#include <windows.h>

int main(int argc, char* argv[])
{
    // set the console to support wide characters
    int result = _setmode(_fileno(stdout), _O_U16TEXT);

    // tell the console to use a supported font.
    CONSOLE_FONT_INFOEX info {};
    info.cbSize = sizeof(info);
    info.dwFontSize.Y = 20;
    wcscpy_s(info.FaceName, L"Courier New");
    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), NULL, &info);

    // print our text
    std::wcout << L"\n\"A veritable smörgåsbord of system functions\"\n\n";
    std::wcout << L"The tetragrammaton is: יהוה" << std::endl;
    std::wcout << L"15€" << std::endl;

    // still problematic for exotic characters (character values > 0xFFFF)
    std::wcout << L"𒀀" << std::endl;
    std::wcout << L"𤭢" << std::endl;
}
