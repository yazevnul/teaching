#include <iostream>
#include <string>
#include <unordered_map>

// Pointer to member function [1]
//
// [1] https://isocpp.org/wiki/faq/pointers-to-members

struct Foo {
    std::string GetHello(int count) const {
        static const std::string hello = "hello";
        std::string res;
        for (int i = 0; i < count; ++i) {
            res += hello;
        }
        return res;
    }
    std::string GetSup(int count) const {
        static const std::string sup = "sup";
        std::string res;
        for (int i = 0; i < count; ++i) {
            res += sup;
        }
        return res;
    }
    std::string GetBye(int count) const {
        static const std::string bye = "bye";
        std::string res;
        for (int i = 0; i < count; ++i) {
            res += bye;
        }
        return res;
    }
};

static std::string CallFunction(const std::string& name, const Foo& foo, int count) {
    // https://isocpp.org/wiki/faq/pointers-to-members#memfnptr-to-const-memfn
    using FunctionPtr = std::string(Foo::*)(int) const;
    static const std::unordered_map<std::string, FunctionPtr> nameToFunctionPtr = {
        {"hello", &Foo::GetHello},
        {"sup", &Foo::GetSup},
        {"bye", &Foo::GetBye}
    };

    const auto it = nameToFunctionPtr.find(name);
    if (it == std::cend(nameToFunctionPtr)) {
        return {};
    }

    return (foo.*(it->second))(count);
}

int main() {
    Foo foo;
    std::cout << CallFunction("hello", foo, 2) << std::endl;
    std::cout << CallFunction("sup", foo, 3) << std::endl;
    std::cout << CallFunction("bye", foo, 10) << std::endl;
    std::cout << CallFunction({}, foo, 2) << std::endl;
}
