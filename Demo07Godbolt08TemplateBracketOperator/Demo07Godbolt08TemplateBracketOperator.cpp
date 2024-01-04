
#include <iostream>

template <typename T, size_t N>
class mysequence {
    T memblock[N];

   public:
    T& operator[](int x);
};

template <typename T, size_t N>
T& mysequence<T, N>::operator[](int x) {
    return memblock[x];
}

int main() {
    mysequence<int, 5> myints;
    mysequence<double, 5> myfloats;
    myints[0] = 100;
    myfloats[3] = 3.1416;
    std::cout << myints[0] << '\n';
    std::cout << myfloats[3] << '\n';
    return 0;
}
