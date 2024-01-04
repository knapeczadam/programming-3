#include <iostream>

int divide(int a, int b, int& result) {
    if (b == 0) {
        return -1;  // Return code indicating division by zero
    }

    result = a / b;
    return 0;  // Return code indicating success
}

int main() {
    int a{10};
    int b{2};
    int result;

    int errorCode = divide(a, b, result);
    if (errorCode == 0) {
        std::cout << "Result: " << result << std::endl;
    } else {
        std::cout << "Error: Division by zero" << std::endl;
    }

    return 0;
}