#include <vector>
#include <array>
#include <iostream>

int main()
{
    // this doesn't work in 32 bit, but will work in 64 bit. Try it out :)
    std::vector<char> vecCharacters(2'000'000'000);

    //std::array<char, 2'000'000'000> arrCharacters;                        // what about this?

    std::cout << vecCharacters.size() << std::endl << std::endl;

    char* char1Ptr = &vecCharacters.back();
    char* char2Ptr = &*(vecCharacters.end() - 1);
    char* char3Ptr = &vecCharacters[vecCharacters.size() - 3];

    std::cout << "char1Ptr: " << (uintptr_t) char1Ptr << std::endl;
    std::cout << "char2Ptr: " << (uintptr_t) char2Ptr << std::endl;
    std::cout << "char3Ptr: " << (uintptr_t) char3Ptr << std::endl << std::endl;

    std::cout << "Difference char3Ptr and char1Ptr: " << (ptrdiff_t)(char3Ptr - char1Ptr) << std::endl;

    std::cin.get();
}
