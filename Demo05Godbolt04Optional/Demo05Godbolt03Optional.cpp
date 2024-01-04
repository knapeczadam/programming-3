
#include <iostream>
#include <optional>

std::optional<int> divide(int a, int b) {
    if (b == 0) {
        return std::nullopt;  // Indicates division by zero
    }

    return a / b;
}

int main() {
    int a{10};
    int b{0};

    auto result = divide(a, b);
    if (result.has_value()) {
        std::cout << "Result: " << result.value() << std::endl;
    } else {
        std::cout << "Error: Division by zero" << std::endl;
    }

    return 0;
}
