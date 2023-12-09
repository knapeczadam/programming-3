#include <iostream>

void substring(const char* source, char* target, int start, int count = -1)
{
    if (count == -1) count = strlen(source) - start;
    int pos = 0;
    while (pos < count and source[start + pos] != '\0')
    {
        target[pos] = source[start + pos];
        pos++;
    }
    target[pos] = '\0';
}

int main()
{
    const char* str = "Hello, World!";
    char substr[100];
    substring(str, substr, 7, 100);
    std::cout << substr;

    std::cin.get();
    return 0;
}
