#include <iostream>
#include <string>
#include <unordered_map>

// Pointer to member function [1]
//
// [1] https://isocpp.org/wiki/faq/pointers-to-members

struct Foo {
    static const std::string kHello;
    static const std::string kSup;
    static const std::string kBye;

    std::string hello;
    std::string sup;
    std::string bye;
};

const std::string Foo::kHello = "hello";
const std::string Foo::kSup = "sup";
const std::string Foo::kBye = "bye";

static void Assign(const std::string& name, const std::string& value, Foo& foo) {
    using MemberPtr = std::string(Foo::*);
    static const std::unordered_map<std::string, MemberPtr> nameToMemberPtr = {
        {"hello", &Foo::hello},
        {"sup", &Foo::sup},
        {"bye", &Foo::bye}
    };

    const auto it = nameToMemberPtr.find(name);
    if (it == std::cend(nameToMemberPtr)) {
        return;
    }

    (foo.*(it->second)) = value;
}

int main() {
    Foo foo;
    Assign("hello", Foo::kHello, foo);
    Assign("sup", Foo::kSup + Foo::kSup, foo);
    Assign("bye", Foo::kBye + Foo::kBye + Foo::kBye, foo);
    Assign({}, Foo::kHello, foo);

    std::cout << foo.hello << ' ' << foo.sup << ' ' << foo.bye << std::endl;
}
