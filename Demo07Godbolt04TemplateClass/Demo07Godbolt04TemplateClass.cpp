
#include <iostream>

template <typename T1, typename T2>
class mypair {
    T1 a;
    T2 b;

   public:
    mypair() {}
    mypair(T1 first, T2 second) : a{first}, b{second} {};
    auto getmax() {
        return a > b ? a : b;
    }
};

int main() {
    mypair<int, double> myobject(100, 3.14);
    std::cout << myobject.getmax();
    return 0;
}
