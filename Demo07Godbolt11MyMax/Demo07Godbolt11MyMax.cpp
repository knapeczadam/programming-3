#include <iostream>

template<typename T>
T my_max(T a, T b) {
    return a > b ? a : b;
}

int main()
{
    int i{1}, j{2};
    float f{3.14}, g{6.28};
    std::cout << my_max(i,j) << "\n";
    std::cout << my_max(f,g) << "\n";
    return 0;
}