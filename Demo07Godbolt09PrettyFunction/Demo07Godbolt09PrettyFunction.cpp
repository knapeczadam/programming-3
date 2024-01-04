#include <iostream>

//#define __PRETTY_FUNCTION__ __FUNCSIG__

int& foo(int& i)
{
    return ++i;
}

float foo(float& f)
{
    return 2.0f * f;
}

template <typename T>
auto fwd(T& t) -> decltype(foo(t))  {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    return foo(t);
}

int main()
{
    int i{0};
    float f{3.14};
    std::cout << fwd(f) << std::endl;
    std::cout << fwd(i) << std::endl;
    return 0;
}