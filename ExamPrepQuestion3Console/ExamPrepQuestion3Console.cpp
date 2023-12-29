#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

class StringTooShortException{};

// bool MyPredicate(const std::string& str, int repeat1, int repeat2)
// {
//     if (repeat1 * repeat2 > str.length())
//         throw StringTooShortException();
//     // int counts[str.size()] = {};
//     std::vector<int> counts(str.size());
//     for (int i = 0, j = 0; i < str.length();++j)
//     {
//         const char c = str[i];
//         counts[j] = 1;
//         while (c == str[++i])
//         {
//             counts[j]++;
//         }
//     }
//     for (int i = 0; i < str.length(); ++i)
//     {
//         if (counts[i] == repeat2)
//         {
//             bool found = true;
//             for (int j = 0, k = i + 1; j < repeat1 - 1 and k < str.length(); ++j, ++k)
//             {
//                 if (counts[k] != repeat2)
//                 {
//                     found = false;
//                     break;
//                 }
//             }
//             if (found) return true;
//         }
//     }
//     return false;
// }

bool MyPredicate(const std::string& str, int repeat1, int repeat2)
{
    if (repeat1 * repeat2 > str.length())
        throw StringTooShortException();

    int count = 0;
    for (int i = 0; i < str.length();)
    {
        const char c = str[i];
        int currentCount = 0;
        while (c == str[i] && i < str.length())
        {
            currentCount++;
            i++;
        }
        if (currentCount == repeat2)
            count++;
        else
            count = 0;

        if (count == repeat1)
            return true;
    }
    return false;
}


int main()
{
    std::cout << MyPredicate("ZeePPoo", 3, 2) << '\n'; // true
    std::cout << MyPredicate("ZeePeePoo", 3, 2) << '\n'; // false
    std::cout << MyPredicate("ZeeP", 3, 2); // exception
}
