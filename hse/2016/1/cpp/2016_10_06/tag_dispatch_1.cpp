#include <iostream>

struct Foo {
    struct Tag {
    };

    static void do_foo() {
        std::cout << "foo" << std::endl;
    }
};

struct Bar {
    struct Tag {
    };

    static void do_bar() {
        std::cout << "bar" << std::endl;
    }
};

template <typename T>
void Do(const T tag);

template <>
void Do<Foo::Tag>(const Foo::Tag) {
    Foo::do_foo();
}

template <>
void Do<Bar::Tag>(const Bar::Tag) {
    Bar::do_bar();
}

template <typename T>
void Do() {
    Do(typename T::Tag());
}

int main() {
    Do<Foo>();
    Do<Bar>();
}
