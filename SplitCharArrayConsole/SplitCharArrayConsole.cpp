
// StringDemo2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

int main()
{
    // using a given input, parse like the console buffer, and print the parts

    // 0.   Set up the starting input
    char inputArr[]{ "calc.exe + 100 50" };

    // 1.   Replace spaces with null terminators = '\0', count how many there are
    int countReplaced{};
    for (char* locationPtr = inputArr; *locationPtr != '\0'; ++locationPtr)
    {
        if (*locationPtr == ' ')
        {
            *locationPtr = '\0';
            ++countReplaced;
        }
    }

    // 2.   Make an array "argumentVectorArr", containing the starting points of the pieces of text inside the string.
    //      Verify your results by using a Watch window (Debug -> Windows -> Watch) to check the values of:
    //          - inputArr
    //          - argumentVectorArr[0]
    //          - argumentVectorArr[1]
    //          - argumentVectorArr[2]
    //          - argumentVectorArr[3]
    //          - argumentVectorArr[4]

    int argumentCount{ countReplaced + 1 };
    char** argumentVectorArr = new char* [argumentCount];

    int argumentVectorIndex{};
    argumentVectorArr[argumentVectorIndex++] = inputArr;

    for (char* locationPtr{ inputArr }; argumentVectorIndex < argumentCount; ++locationPtr)
    {
        if (*locationPtr == '\0')
        {
            argumentVectorArr[argumentVectorIndex++] = locationPtr + 1;
        }
    }

    // 3.   Print the pieces of text to the output using std::cout
    for (int index{}; index < argumentCount; ++index)
    {
        std::cout << argumentVectorArr[index] << std::endl;
    }

    // 4.   Release the dynamic array
    delete[] argumentVectorArr;
}
