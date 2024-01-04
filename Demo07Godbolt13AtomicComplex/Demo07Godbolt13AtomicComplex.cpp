#include <atomic>
#include <complex>
#include <iostream>

template <typename T>
auto my_max(T a, T b) {
    return a > b ? a : b;
}

int main() {
    std::complex<float> c1, c2;
    std::atomic<int> ai1, ai2;
    std::cout << my_max(c1, c2) << "\n";
    std::cout << my_max(ai2, ai2) << "\n";
    return 0;
}