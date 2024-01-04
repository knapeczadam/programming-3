#include <iostream>

struct B
{
    B(){ std::cout << "B()" << std::endl; }
    ~B(){ std::cout << "~B()" << std::endl; }
};

struct A
{
    B b;
    A(){ std::cout << "A()" << std::endl; throw std::exception(); }
    ~A(){ std::cout << "~A()" << std::endl; }
};

int main()
{
    try
    {
        A a;
    }
    catch(const std::exception& ex)
    {
        std::cout << ex.what() << std::endl;
    }
    std::cout << "No catch -> terminate!!!" << std::endl;
    A aa;
    return 0;
}