#include <iostream>
#include <functional>
#include <vector>
using std::cout, std::endl;           // this needs C++17 to work: Properties -> C++ Language Standard
using namespace std::placeholders;

#include "TestStuff.h"

void RunStdFunctionDemo();
void RunSimpleEventSystemDemo();
void RunMemberFunctionEventSystemDemo();
void RunLambdaBindComboDemo();

int main()
{
    RunStdFunctionDemo();
    //RunSimpleEventSystemDemo();
    //RunMemberFunctionEventSystemDemo();
    //RunLambdaBindComboDemo();
}

void RunStdFunctionDemo()
{
    Test test1{1}, test2{2};
    cout << endl;

    //////////////////////////////
    // Non-member function behavior
    //////////////////////////////

    // Make a void(int) function wrapper
    std::function<void(int)> myFunctionWrapper;             // stores any callable object which takes an int and returns void

    // 1 : function pointer   
    myFunctionWrapper = &Print;                             // store a void(*)(int) function pointer
    myFunctionWrapper(1);

    // 2 : functor = class with overloaded operator()
    myFunctionWrapper = PrintFunctor{};                     // store a void(int) function object: has a "void operator()(int)" function
    myFunctionWrapper(2);

    // 3 : lambda = anonymous, inline functor
    myFunctionWrapper = [](int nr) -> void                  // store a void(int) lambda object; the return type specification is optional
    {
        cout << "Lambda [](int) prints " << nr << endl;
    };
    myFunctionWrapper(3);

    // 4 : binder = anonymous function object, based on another, existing callable object
    myFunctionWrapper = std::bind(&PrintTimes, _1, 1);      // store a void(int) binder object. Starting from a void(int, int) function,  
    myFunctionWrapper(4);                                   // fix the 2nd parameter to the value 4 => only 1 parameter left

    // 5 : static member function pointer (doesn't have a hidden this pointer)
    myFunctionWrapper = &Test::PrintNrObjects;              // store a static member function
    myFunctionWrapper(5);

    // 6 : binder, turns a member function into non-member function notation (by binding the member object)
    myFunctionWrapper = std::bind(&Test::PrintMultiplied, &test1, _1);           // create a normal function by fixing the this-pointer (!)
    myFunctionWrapper(6);

    //////////////////////////////
    // Member function pointers
    //////////////////////////////
    // Make a void (Test::*)(int) member function wrapper. 
    std::function<void(Test*, int)> myMemberFunctionWrapper;       // stores any member function of Test which takes an int and returns void

    // 7 : member function pointer
    myMemberFunctionWrapper = &Test::PrintMultiplied;   // store a void(Test::*)(int) member function pointer
    myMemberFunctionWrapper(&test1, 7);

    // 8 : binds to a std::function wrapper for a member function taking 1 argument, based on a member function taking 2 arguments
    myMemberFunctionWrapper = std::bind(&Test::PrintMultipliedTimes, _1, _2, 8);                        // starts from a function with 3 (!) parameters, fixes the last one
    myMemberFunctionWrapper(&test1, 1);

    //// 9 : mem_fn adaptor for auto notation to bind member functions
    //std::function<void(Test, int, int)> memberFunction = &Test::PrintMultipliedTimes;                 // this works without std::mem_fn
    auto memberFunction = std::mem_fn(&Test::PrintMultipliedTimes);                                     // auto needs std::mem_fn to work
    memberFunction(test1, 1, 9); 
}

void RunSimpleEventSystemDemo()
{
    //////////////////////////////
    // event system: a vector of simple std::functions
    //////////////////////////////
    Test test1{1}, test2{2};

    // vector of event functions. In a larger project, this would be a datamember of an event manager class
    std::vector<std::function<void(int)>> vecEventFunctions;

    // fill in
    vecEventFunctions.push_back(&Print);                                        // function
    vecEventFunctions.push_back(PrintFunctor{});                                // functor
    vecEventFunctions.push_back([](int nr)                                      // lambda
        {
            cout << "Lambda print function " << nr << endl;
        });
    vecEventFunctions.push_back(std::bind(&PrintTimes, _1, 4));                 // binder
    vecEventFunctions.push_back(&Test::PrintNrObjects);                         // static member function   
    vecEventFunctions.push_back(std::bind(&Test::PrintMultiplied, &test1, _1)); // binder with member function + bound object

   // execute all events
    int value{};
    for (auto& event : vecEventFunctions)
    {
        event(++value);
    }
}

void RunMemberFunctionEventSystemDemo() 
{
    //////////////////////////////
    // OO event system: a vector of pairs of object pointers and the member functions to call
    //////////////////////////////
    Test test1{}, test2{};

    // vector of pair of addres of an objects + the member function to call on it. In a larger project, this would be a datamember of an advanced event manager class
    using std::vector, std::function, std::pair;                             // you can do this, but you don't have to. See next line.
    vector<pair<Test*, function<void(Test*)>>> vecEventMemberFunctions;      // note the absence of std namespace spam, because of the previous line

    vecEventMemberFunctions.push_back({ &test1, &Test::IncrementValue });
    vecEventMemberFunctions.push_back({ &test1, &Test::IncrementValue });
    vecEventMemberFunctions.push_back({ &test1, &Test::DoubleValue });
                                        
    vecEventMemberFunctions.push_back({ &test2, &Test::IncrementValue });
    vecEventMemberFunctions.push_back({ &test2, &Test::IncrementValue });
    vecEventMemberFunctions.push_back({ &test2, &Test::IncrementValue });
    
    vecEventMemberFunctions.push_back({ &test2, std::bind(&Test::PrintMultiplied, _1, 10)});

    // execute list of events. 
    for (auto& event : vecEventMemberFunctions)
    {
        event.second(event.first);            
    }

    // print results
    test1.Print();
    test2.Print();
}

void RunLambdaBindComboDemo()
{
    int number1{ 0 }, number2{ 1 };
    cout << std::boolalpha;

    auto IsAGreaterThanB =  std::bind([](int* firstPtr, int* secondPtr) {
                                return *firstPtr > *secondPtr;
                            }, &number1, &number2);

    cout << IsAGreaterThanB() << endl;
    number1 = 2;
    cout << IsAGreaterThanB() << endl;
}