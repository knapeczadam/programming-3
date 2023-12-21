// ExamPrepQuestion1Console.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <tchar.h>
#include <chrono>
#include <vector>
#include <algorithm>
#include <numeric>
#include <ctime>
#include <random>
#include <cassert>

template <typename T>
void DeleteMinMax(std::vector<T>& v)
{
    assert(v.size() >= 2, "Vector must have at least 2 elements");
    std::sort(std::begin(v), std::end(v));
    v.erase(std::begin(v));
    v.erase(std::end(v) - 1);
}

template <typename callable, typename container>
auto MeasureTimeV1(callable& func, container& data)
{
    constexpr int numMeasurements = 10;
    std::vector<long long> measurements;
    measurements.reserve(numMeasurements);

    for (int i = 0; i < numMeasurements; i++)
    {
        const auto start = std::chrono::high_resolution_clock::now();
        func(data);
        const auto end = std::chrono::high_resolution_clock::now();

        const auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        measurements.push_back(duration);
    }

    // Remove the largest and smallest measurements
    DeleteMinMax(measurements);

    // Calculate the average
    const auto averageTime = std::accumulate(std::begin(measurements), std::end(measurements), 0.0) / static_cast<double>(measurements.size());
    return averageTime;
}


template <typename callable, typename container>
auto MeasureTimeV2(callable& func, container& data)
{
    constexpr int numMeasurements = 10;
    std::vector<long long> measurements;
    measurements.reserve(numMeasurements);

    for (int i = 0; i < numMeasurements; i++)
    {
        const auto start = std::chrono::high_resolution_clock::now();
        func(data);
        const auto end = std::chrono::high_resolution_clock::now();

        const auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        measurements.push_back(duration);
    }

    // Remove the largest and smallest measurements
    DeleteMinMax(measurements);

    // Calculate the average
    const auto averageTime = std::accumulate(std::begin(measurements), std::end(measurements), 0.0) / static_cast<double>(measurements.size());
    return averageTime;
}

template <typename callable, typename container, typename time>
auto MeasureTimeV3(callable& func, container& data)
{
    constexpr int numMeasurements = 10;
    std::vector<long long> measurements;
    measurements.reserve(numMeasurements);

    for (int i = 0; i < numMeasurements; i++)
    {
        const auto start = std::chrono::high_resolution_clock::now();
        func(data);
        const auto end = std::chrono::high_resolution_clock::now();

        const auto duration = std::chrono::duration_cast<time>(end - start).count();
        measurements.push_back(duration);
    }

    // error-prone
    // Remove the largest and smallest measurements
    // const auto mixMax = std::minmax_element(std::begin(measurements), std::end(measurements));
    // measurements.erase(mixMax.first);
    // measurements.erase(mixMax.second);
    DeleteMinMax(measurements);

    // Calculate the average
    const auto averageTime = std::accumulate(measurements.begin(), measurements.end(), 0.0) / static_cast<double>(measurements.size());
    return averageTime;
}

struct MyCustomSort
{
    void operator()(std::vector<int>& v) const
    {
        std::sort(v.begin(), v.end(), [](int a, int b) { return a > b; });
    }
};

int _tmain(int argc, _TCHAR* argv[])
{
    // seed the random number generator
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    constexpr int numOfElements = 1000000;
    std::vector<int> test(numOfElements);
    for (int i = 0; i < numOfElements; i++)
    {
        test[i] = std::rand();
    }

    // Create the callable objects
    auto myCustomSort1 = [](std::vector<int>& v)
    {
        std::sort(v.begin(), v.end(), [](int a, int b) { return a > b; });
    };

    // Create the callable objects
    MyCustomSort myCustomSort2;

    //--------------------------------------------------------------------------------
    // Version 1
    //--------------------------------------------------------------------------------
    const auto averageTime1 = MeasureTimeV1(myCustomSort1, test);
    std::cout << "Version 1\n";
    std::cout << "Average time: " << averageTime1 << " milliseconds\n";
    std::cout << "\n";

    //--------------------------------------------------------------------------------
    // Version 2
    //--------------------------------------------------------------------------------
    const auto averageTime2 = MeasureTimeV2(myCustomSort1, test);
    std::cout << "Version 2\n";
    std::cout << "Average time: " << averageTime2 << " milliseconds\n";
    std::cout << "\n";
    
    //--------------------------------------------------------------------------------
    // Version 3
    //--------------------------------------------------------------------------------
    const auto averageTime3 = MeasureTimeV3<MyCustomSort, std::vector<int>, std::chrono::microseconds>(myCustomSort2, test);
    std::cout << "Version 3\n";
    std::cout << "Average time: " << averageTime3 << " microseconds\n";
    // std::cout << "Average time: " << averageTime3 / 1000.0 << " milliseconds\n";
    std::cout << "\n";
}
