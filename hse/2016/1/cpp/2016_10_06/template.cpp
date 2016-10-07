#include <iostream>
#include <typeinfo>

template <typename T>
struct Foo {
    template <typename U>
    void Do() const {
        std::cout << typeid(U).name() << std::endl;
    }
};

template <typename T, typename U>
void Bar(const Foo<T> foo) {
    foo.template Do<U>();
}

int main() {
    Foo<int> foo;
    Bar<int, float>(foo);
}
