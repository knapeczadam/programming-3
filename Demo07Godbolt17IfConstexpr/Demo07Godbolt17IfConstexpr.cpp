#include <iostream>
#include <memory>
// if constexpr since C++17
auto get_value(auto t) {
    if constexpr (std::is_pointer_v<decltype(t)>)
        return *t;
    else
        return t;
}

void check(auto v1, auto v2) {
    if constexpr (std::is_same<decltype(v1), decltype(v2)>()) {
        std::cout << "They have the same type!\n";
    } else {
        std::cout << "They have different types!\n";
    }
}

//int get_value(int t) { return t; }

//int get_value(int* p) { return *p; }

int main() {
    int i = 9;
    auto pi = &i;
    check(i, pi);
    std::cout << get_value(pi) << "\n";
    std::cout << get_value(i) << "\n";
}