#include <iostream>
#include <type_traits>
#include <memory>

// Why we don't want to tell you about memory and pointers yet.

class Foo {
    std::string bar_{"something"};

public:
    Foo() {
        std::cout << "ctor bar=" << bar_ << std::endl;
    }

    ~Foo() {
        std::cout << "dtor bar=" << bar_ << std::endl;
    }
};

int main() {
    // alignof [1]
    //
    // http://en.cppreference.com/w/cpp/language/alignof
    std::aligned_storage_t<sizeof(Foo), alignof(Foo)> storage;
    // placement new [1]
    //
    // [1] http://en.cppreference.com/w/cpp/language/new
    new (&storage) Foo();

    // `Foo::bar_` leaks! because dtor for Foo wasn't called.
}
