#include <iostream>
#include <memory>

auto constexpr pi(int n_cycles) {
    double sum{0.0};
    int sign{1};
    for (int i{}; i < n_cycles; ++i) {
        sum += sign / (2.0 * i + 1.0);
        sign *= -1;
    }
    return 4.0 * sum;
}

int main() {
    constexpr auto x = pi(300'000);
    std::cout << x << "\n";
}