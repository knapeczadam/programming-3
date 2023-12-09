#include <iostream> // std::cout, std::endl
#include <string>   // std::string
#include <locale>   // std::locale, std::tolower

#if 0
char ToLower(char c)
{
    if (c >= 'A' and c <= 'Z')
    {
        c += 'a' - 'A';
    }
    return c;
}
#else
char ToLower(char c)
{
    if (c >= 65 and c <= 90)
    {
        c += 32;
    }
    return c;
}
#endif

int main()
{
    std::cout << "Enter a string: ";
    std::string str;
    std::getline(std::cin, str);
    std::cout << "You entered: " << str << '\n';
    //--------------------------------------------------------------------------------
    std::cout << "Using ToLower(c): ";
    for (char c : str)
    {
        std::cout << ToLower(c);
    }
    //--------------------------------------------------------------------------------
    std::cout << '\n';
    std::cout << "Using std::tolower(c): ";
    for (char c : str)
    {
        std::cout << std::tolower(c);
    }
    //--------------------------------------------------------------------------------
    std::cout << '\n';
    std::cout << "Using std::tolower( std::locale()): ";
    for (char c : str)
    {
        std::cout << std::tolower(c, std::locale());
    }

    std::cin.get();
    return 0;
}