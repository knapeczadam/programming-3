
#include <iostream>

template <class T>
class mycontainer {
    T element;

   public:
    mycontainer(T arg) { element = arg; }
    T increase() { return ++element; }
};

int main() {
    mycontainer<int> myint(7);
    mycontainer<char> mychar('j');
    std::cout << myint.increase() << std::endl;
    std::cout << mychar.uppercase() << std::endl;
    return 0;
}
