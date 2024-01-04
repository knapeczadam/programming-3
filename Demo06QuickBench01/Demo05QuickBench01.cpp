// https://quick-bench.com/q/kUlEvyt0VyJl1HG19JaPD1W0SyU
int divide(int a, int b, int& result) {
    if (b == 0) {
        return -1;  // Return code indicating division by zero
    }

    result = a / b;
    return 0;  // Return code indicating success
}

class DivideByZeroException {};

int divideWithException(int a, int b) {
    if (b == 0) {
        throw DivideByZeroException();
    }

    return a / b;
}

#include <optional>

std::optional<int> divideWithOptional(int a, int b) {
    if (b == 0) {
        return std::nullopt;  // Indicates division by zero
    }

    return a / b;
}

int a{10};
int b{5};
int result{};

// static void errorCode(benchmark::State& state) {
//   for (auto _ : state) {
//     int errorCode = divide(a, b, result);
//     benchmark::DoNotOptimize(errorCode);
//   }
// }
// BENCHMARK(errorCode);
//
// static void errorCodeWithError(benchmark::State& state) {
//   for (auto _ : state) {
//     int errorCode = divide(a, 0, result);
//     benchmark::DoNotOptimize(errorCode);
//   }
// }
// BENCHMARK(errorCodeWithError);
//
// static void Exception(benchmark::State& state) {
//   for (auto _ : state) {
//     result = divideWithException(a, b);
//     benchmark::DoNotOptimize(result);
//   }
// }
// BENCHMARK(Exception);
//
// static void exceptionThrows(benchmark::State& state) {
//   for (auto _ : state) {
//   try {
//     result = divideWithException(a, 0);
//   } 
//   catch(DivideByZeroException e) {
//   }
//     benchmark::DoNotOptimize(result);
//   }
// }
// BENCHMARK(exceptionThrows);
//
// static void Optional(benchmark::State& state) {
//   for (auto _ : state) {
//     auto result = divideWithOptional(a, b);
//     benchmark::DoNotOptimize(result);
//   }
// }
// BENCHMARK(Optional);
//
// static void optionalEmpty(benchmark::State& state) {
//   for (auto _ : state) {
//     auto result = divideWithOptional(a, 0);
//     benchmark::DoNotOptimize(result);
//   }
// }
// BENCHMARK(optionalEmpty);
