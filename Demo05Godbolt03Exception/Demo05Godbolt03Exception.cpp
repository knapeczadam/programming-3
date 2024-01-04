#include <iostream>
#include <stdexcept>

class DivideByZeroException {};

int divide(int a, int b) {
    if (b == 0) {
        throw DivideByZeroException();
    }

    return a / b;
}

int main() {
    int a{10};
    int b{0};

    try {
        int result = divide(a, b);
        std::cout << "Result: " << result << "\n";
    } catch (const DivideByZeroException& ex) {
        std::cout << "Exception thrown \n";
    }

    return 0;
}
