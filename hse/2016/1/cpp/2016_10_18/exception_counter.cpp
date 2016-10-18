#include <chrono>
#include <exception>
#include <iostream>
#include <string>
#include <unordered_map>

using Timestamps = std::unordered_map<std::string, std::chrono::microseconds>;
using ExceptionCounter = std::unordered_map<std::string, size_t>;

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

static ExceptionCounter& GetGlobalExceptionCounter() {
    static ExceptionCounter counter;
    return counter;
}

class GuardExceptionCounter {
    std::string name_;
    ExceptionCounter& counter_;

public:
    GuardExceptionCounter(const std::string& name, ExceptionCounter& counter)
        : name_{name}
        , counter_{counter} {
    }

    explicit GuardExceptionCounter(const std::string& name)
        : GuardExceptionCounter{name, GetGlobalExceptionCounter()} {
    }

    ~GuardExceptionCounter() {
        if (std::uncaught_exception()) {
            ++counter_[name_];
        }
    }
};

#define Y_GUARD(name)                                                  \
    GuardTimer guard_timer_##__COUNTER__{name};                        \
    GuardExceptionCounter guard_exception_counter_##__COUNTER__{name};

static size_t ComputeSum(size_t n) {
    GuardTimer timer{"compute_sum"};

    size_t sum = 0;
    for (size_t i = 0; i < n; ++i) {
        sum += i;
    }

    return sum;
}

[[noreturn]] static void ThrowException()  {
    Y_GUARD("throw_exception")
    throw std::runtime_error("wow, exception!");
}

static void PrintGlobalTimestamps(std::ostream& out) {
    out << "Global timestamps are" << '\n';
    for (const auto& kv : GetGlobalTimestamps()) {
        out << kv.first << ' ' << kv.second.count() << '\n';
    }
}

static void PrintGlobalExceptionCounters(std::ostream& out) {
    out << "Global exception counters are" << '\n';
    for (const auto& kv : GetGlobalExceptionCounter()) {
        out << kv.first << ' ' << kv.second << '\n';
    }
}

int main(int, char** argv) {
    PrintGlobalTimestamps(std::cout);
    PrintGlobalExceptionCounters(std::cout);
    const size_t n = static_cast<size_t>(std::atoi(argv[1]));

    const auto sum = ComputeSum(n);
    std::cout << sum << std::endl;

    try {
        ThrowException();
    } catch (std::runtime_error&) {
    }

    PrintGlobalTimestamps(std::cout);
    PrintGlobalExceptionCounters(std::cout);
}
