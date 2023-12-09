#include <iostream> // std::cout,   std::cin
#include <locale>   // std::locale, std::toupper
#include <string>   // std::string, std::getline

#if 0
char ToUpper(char c)
{
    if (c >= 'a' && c <= 'z')
    {
        c -= ('a' - 'A');
    }
    return c;
}
#else
char ToUpper(char c)
{
    if (c >= 97 and c <= 122)
    {
        c -= 32;
    }
    return c;
}
#endif

void ToUpper(char* str)
{
   for (int i = 0; str[i] != '\0'; ++i)
   {
       str[i] = ToUpper(str[i]);
   } 
}

int main()
{
    std::cout << "Enter a string: ";
    std::string str;
    std::getline(std::cin, str);
    std::cout << "You entered: " << str << '\n';
    //-------------------------------------------------------------------------
    std::cout << "Using ToUpper(c): ";
    for (char c : str)
    {
        std::cout << ToUpper(c);
    }
    //-------------------------------------------------------------------------
    std::cout << '\n';
    std::cout << "Using std::toupper(c): ";
    for (char c : str)
    {
        std::cout << std::toupper(c);
    }
    //-------------------------------------------------------------------------
    std::cout << '\n';
    std::cout << "Using std::toupper(c, std::locale()): ";
    for (char c : str)
    {
        std::cout << std::toupper(c, std::locale());
    }
    //-------------------------------------------------------------------------
    std::cout << '\n';
    char cstr[] = "Hello, World!";
    ToUpper(cstr);
    std::cout << "Using ToUpper(cstr): " << cstr << '\n';

    std::cin.get();
    return 0; 
}
