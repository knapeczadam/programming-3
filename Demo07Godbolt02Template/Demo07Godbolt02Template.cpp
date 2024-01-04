
#include <iostream>

template <class T>
T GetMax (T a, T b) {
  T result;
  result = (a>b)? a : b;
  return (result);
}

int main () {
  int i{5}, j{6};
  long l{10}, m{5};
  int k = GetMax<int>(i,j);
  std::cout << k << std::endl;
  long n = GetMax<long>(l,m);
  std::cout << n << std::endl;
  return 0;
}
