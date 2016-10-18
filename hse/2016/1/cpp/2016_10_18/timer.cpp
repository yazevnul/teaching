#include <chrono>
#include <iostream>
#include <string>
#include <unordered_map>

// RAII -- Resource Acuisition is Initialization [1, 2]
//
// [1] http://en.cppreference.com/w/cpp/language/raii
// [2] https://en.wikipedia.org/wiki/Resource_acquisition_is_initialization

using Timestamps = std::unordered_map<std::string, std::chrono::microseconds>;

// Singleton [1]
//
// [1] https://en.wikipedia.org/wiki/Singleton_pattern
static Timestamps& GetGlobalTimestamps() {
    static Timestamps timestamps;
    return timestamps;
}

class Timer {
    std::chrono::high_resolution_clock clock_;
    std::chrono::time_point<std::chrono::high_resolution_clock> start_;

public:
    Timer()
        : start_{clock_.now()} {
    }

    std::chrono::microseconds GetTimeFromCtor() {
        return std::chrono::duration_cast<std::chrono::microseconds>(
            clock_.now() - start_);
    }
};

class GuardTimer {
    Timer timer_;
    std::string name_;
    Timestamps& timestamps_;

public:
    GuardTimer(const std::string& name, Timestamps& timestamps)
        : name_{name}
        , timestamps_{timestamps} {
    }

    explicit GuardTimer(const std::string& name)
        : GuardTimer(name, GetGlobalTimestamps()) {
    }

    ~GuardTimer() {
        timestamps_[name_] = timer_.GetTimeFromCtor();
    }
};

// Define helper macros [1, 2].
//
// __COUNTER__ [3] is a language extension supported by GCC and Clang. There is also __LINE__
// supported by all compilers, you can fall back to __LINE__ in MSVC.
//
// [1] http://en.cppreference.com/w/cpp/preprocessor
// [2] http://google.github.io/styleguide/cppguide.html#Macro_Names
// [3] http://clang.llvm.org/docs/LanguageExtensions.html#builtin-macros
#define Y_TIMER(name) \
    GuardTimer guard_timer_##__COUNTER__{name};

static size_t ComputeSum(size_t n) {
    GuardTimer timer{"compute_sum"};

    size_t sum = 0;
    for (size_t i = 0; i < n; ++i) {
        sum += i;
    }

    return sum;
}

// This function doesn't return. And compiler will warn us about it. So we add explicit attribute to
// fix the warning.
//
// [1] http://clang.llvm.org/docs/AttributeReference.html#id2
[[noreturn]] static void ThrowException()  {
    Y_TIMER("throw_exception")
    throw std::runtime_error("wow, exception!");
}

static void PrintGlobalTimestamps(std::ostream& out) {
    out << "Global timestamps are" << '\n';
    for (const auto& kv : GetGlobalTimestamps()) {
        out << kv.first << ' ' << kv.second.count() << '\n';
    }
}

int main(int, char** argv) {
    PrintGlobalTimestamps(std::cout);
    const size_t n = static_cast<size_t>(std::atoi(argv[1]));

    const auto sum = ComputeSum(n);
    std::cout << sum << std::endl;

    try {
        ThrowException();
    } catch (std::runtime_error&) {
    }

    PrintGlobalTimestamps(std::cout);
}
