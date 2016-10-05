#include <iostream>
#include <string>

// fixed-width types are great, use them!
#include <cstdint>

// Another example of template metaprogramming. Here we evaluating Fibonacci numbers at compile
// time.

// We are going to instantiate `FibonacciNumber` for each Fibonacci number. Just try to compile
// program with `FibonacciNumber<10000>::value` and see what compiler will tell you.
template <uint16_t N>
struct FibonacciNumber {
    static const uint64_t value = FibonacciNumber<N - 1>::value +
                                  FibonacciNumber<N - 2>::value;
};

// Variable templates [1] are here to save typing for you! Unfortuanatelly they are C++14 language
// feature and won't be available for you in your homework contests (they are all tested with
// `--std=c++11`).
//
// [1] http://en.cppreference.com/w/cpp/language/variable_template
template <uint16_t N>
constexpr auto FibonacciNumberValue = FibonacciNumber<N>::value;

template <>
struct FibonacciNumber<0> {
    static const uint64_t value = 0;
};

template <>
struct FibonacciNumber<1> {
    static const uint64_t value = 1;
};

// `constexpr` stands for "constant expression" [1]
//
// [1] http://en.cppreference.com/w/cpp/language/constant_expression
constexpr uint64_t FibonacciNumberCE(const uint16_t n) noexcept {
    if (0 == n) {
        return 0;
    } else if (1 == n) {
        return 1;
    }

    // yep, recursion is allowed for constant expressions, but there are limits too. Try compiling
    // `FibonacciNumberCE(10000)` it won't be done at compile time! (use debugger to see what will
    // happen at runtime)
    return FibonacciNumberCE(n - 1) + FibonacciNumberCE(n - 2);
}

template <uint16_t N>
struct FibonacciNumberS {
    // Template is not recursive, but constexpr function is. Try compiling program with
    // `FibonacciNumberS<10000>::value` and see what will happen (error message will be similar to
    // the one triggered by `FibonacciNumber<10000>::value` in the first example.
    static constexpr uint64_t value = FibonacciNumberCE(N);
};

int main() {
    std::cout << FibonacciNumber<0>::value << std::endl;
    std::cout << FibonacciNumber<1>::value << std::endl;
    std::cout << FibonacciNumber<10>::value << std::endl;

    std::cout << FibonacciNumberValue<0> << std::endl;
    std::cout << FibonacciNumberValue<1> << std::endl;
    std::cout << FibonacciNumberValue<10> << std::endl;

    std::cout << FibonacciNumberS<0>::value << std::endl;
    std::cout << FibonacciNumberS<1>::value << std::endl;
    std::cout << FibonacciNumberS<10>::value << std::endl;

    std::cout << FibonacciNumberCE(0) << std::endl;
    std::cout << FibonacciNumberCE(1) << std::endl;
    std::cout << FibonacciNumberCE(10) << std::endl;
}
