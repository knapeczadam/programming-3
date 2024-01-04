#include <concepts>
#include <iostream>

template <typename T>
concept HasMethodA = requires(T t) {
    { t.method_a() } -> std::integral;
};
// t.method_a() is a valid expression returning an integral type

template <typename T>
concept HasMethodB = requires(T t) {
    { t.method_b() } -> std::floating_point;
};
// t.method_b() is a valid expression returning a floating point type

template <typename T>
concept HasBothMethods = HasMethodA<T> && HasMethodB<T>;
// satisfies both HasMethodA and HasMethodB concepts

// For concept X = A && B, X is more specific than either A or B
// For concept X = A || B, X is less specific than either A or B

struct X {
    int method_a() { return {}; }
};

struct Y {
    float method_b() { return {}; }
};

struct Z {
    int method_a() { return {}; }
    float method_b() { return {}; }
};

// Overloads with different constraints:
void some_function(HasMethodA auto&&) { std::cout << "HasMethodA\n"; }
void some_function(HasMethodB auto&&) { std::cout << "HasMethodB\n"; }
void some_function(HasBothMethods auto&&) { std::cout << "HasBothMethods\n"; }

int main() {
    some_function(X{});  // MethodA variant, X only satisfies HasMethodA
    some_function(Y{});  // MethodB variant, Y only satisfies HasMethodB
    some_function(Z{});  // BothMethods variant
    // Z satisfies HasMethodA, HasMethodB and HasBothMethods
}