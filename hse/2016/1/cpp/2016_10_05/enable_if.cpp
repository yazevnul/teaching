#include <iostream>
#include <string>
#include <type_traits>
#include <vector>

// Quick example of SFINAE [1] (acronym for "Substitution Failure is not an Error").
// This language feature is typically used in template metaprogramming [2] (program that executes in
// compile time).
//
// [1] https://en.wikipedia.org/wiki/Template_metaprogramming
// [2] http://en.cppreference.com/w/cpp/language/sfinae

// Here we are doing compile time analysis of properties of type `T` and based on them decide if one
// of `PrintSomething` would be instantiated.
//
// See http://en.cppreference.com/w/cpp/types/enable_if
template <typename T>
std::enable_if_t<std::is_pod<T>::value, void>
PrintSomething() {
    std::cout << "[T is POD type]" << std::endl;
}

template <typename T>
std::enable_if_t<!std::is_pod<T>::value, void>
PrintSomething() {
    std::cout << "[T is no POD]" << std::endl;
}

// `Foo` is POD (acronym for "Plain Old Data"); basically, any type that can be copied via `memcpy`
// is POD.
// See related type trait [1] and wiki article on the subject [2] for details.
//
// [1] http://en.cppreference.com/w/cpp/types/is_pod
// [2] https://en.wikipedia.org/wiki/Passive_data_structure
struct Foo {
};

// `Bar` is not POD, because `std::string` is not POD.
struct Bar {
    std::string baz;
};

int main() {
    PrintSomething<int>();
    PrintSomething<std::string>();
    PrintSomething<Foo>();
    PrintSomething<Bar>();
}
