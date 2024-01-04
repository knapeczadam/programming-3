
#include <iostream>

template <typename T>
class mypair {
    T a, b;

   public:
    mypair(){}
    mypair(T first, T second) {
        a = first;
        b = second;
    }
    T getmax();
};

template <typename T>
T mypair<T>::getmax() {
    T retval;
    retval = a > b ? a : b;
    return retval;
}

int main() {
    mypair<int> myobject(100, 75);    
    std::cout << myobject.getmax();
    return 0;
}
