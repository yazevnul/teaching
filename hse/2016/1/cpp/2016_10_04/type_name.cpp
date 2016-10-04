#include <iostream>
#include <typeinfo> // required for `typeid`

struct MyLovelyType {
};

namespace {
    struct AnonymousType {
    };
}

int main() {
    // see http://en.cppreference.com/w/cpp/language/typeid
    std::cout << typeid(MyLovelyType).name() << std::endl;
    // will write something like `12MyLovelyType`, this is a mangled [1] name of the type.
    // To unmangle it pass it to `c++filt` program.
    //
    // clang++ --std=c++14 type_name.cpp && ./a.out | c++filt
    //
    // The output will be `MyLovelyType`.
    //
    // [1] https://en.wikipedia.org/wiki/Name_mangling

    {
        using Foo = MyLovelyType;
        Foo foo;
        std::cout << typeid(foo).name() << std::endl; // MyLovelyType
        std::cout << typeid(static_cast<const Foo&>(foo)).name() << std::endl; // MyLovelyType
        std::cout << typeid(&foo).name() << std::endl; // MyLovelyType*
        std::cout << typeid(&static_cast<const Foo&>(foo)).name() << std::endl; // const MyLovelyType*
    }

    {
        std::cout << typeid(AnonymousType).name() << std::endl; // (anonymous namespace)::AnonymousType
    }
}
