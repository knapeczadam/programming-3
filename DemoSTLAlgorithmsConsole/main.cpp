// Demo.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <numeric>
#include <string>
using std::cout, std::endl;
using namespace std::placeholders;

template <typename Param1, typename Param2>
auto add(Param1 x, Param2 y) 
{
    return x + y;
}

int main()
{
    // 1. function versus functor with auto. No practical use; it's just a demo.
    auto sum = add(5, 7);
    auto sum2 = std::plus{}(5, 7);  // i'm using the predefined functor std::plus<>, see p. 486. Do you see how this works?

    // 2. some STL algorithms and functors
    std::vector<int> numbers{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    // 2.a. Algorithm accepting an iterator to print a range to output
    cout << "Numbers: ";

    std::copy(numbers.begin(), numbers.end(), std::ostream_iterator<int>{cout, " "});

    cout << endl << endl;

    // 2.b. Algorithm with unary predicate using a lambda 
    int64_t count = std::count_if(numbers.begin(), numbers.end(), [](auto element)
    {
        return element % 2;
    });

    cout << "Number of odd elements = " << count << endl << endl;

    // 2.c. Algorithm with binary predicate 
    bool isSorted = std::is_sorted( numbers.begin(), numbers.end(),  // range
                                    std::greater{});                 // sort criterion

    cout << "The numbers are sorted in descending order: " << std::boolalpha << isSorted << endl << endl;

    // 2.d. Algorithm with unary function, first with lambda, then with binder 
    std::transform( numbers.begin(), numbers.end(),                  // range
                    numbers.begin(),                                 // destination
                    [](auto element) {                               // operation
                        return element * 5;
                    });

    std::transform( numbers.begin(), numbers.end(),                  // range
                    numbers.begin(),                                 // destination
                    std::bind(std::multiplies{}, _1, 5));            // operation

    // 2.e. Algorithm with binary function 
    int64_t result = std::accumulate( numbers.begin(), numbers.end(),   // range
                                     -1,                                // starting value
                                     std::multiplies{});                // operation

    cout << "Cumulative multiplication with -1: " << result << endl << endl;

    // 2.f. Algorithm with unary procedure
    std::cout << "Printing lower range, twice:" << endl;

    std::for_each(  numbers.begin(),                                                        // start range
                    find_if(numbers.begin(), numbers.end(), [&](auto element) {             // end range
                        return element > std::accumulate(numbers.begin(), numbers.end(), 0.0) / numbers.size();
                    }),
                    [](auto element) {                                                      // operation
                        cout << element << " ";
                    });

    cout << endl;

    // 2.g. Same as 2.f, but end range with std::bind() and std::greater<> instead of lambda
    std::for_each(  numbers.begin(),                                                        // start range
                    find_if(numbers.begin(), numbers.end(), std::bind(std::greater{}, _1,   // end range
                            std::accumulate(numbers.begin(), numbers.end(), 0.0) / numbers.size())),
                    [](auto element) {                                                      // operation
                        cout << element << " ";
                    });

    cout << endl;
}