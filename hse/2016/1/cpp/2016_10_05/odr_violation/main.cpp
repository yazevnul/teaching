#include "h.h"

// clang++ -g --std=c++14 main.cpp -o odr_violation a.cpp b.cpp && ./odr_violation
//
// An example of violation of ODR [1] (acronym for "One Definition Rule").
//
// - Try changing the order of a.cpp and b.cpp.
// - Try attacing with debugger to see what is happing.
// - Try setting different optimization levels `-O0`, `-O1`, `-O2`, `-O3`, `-Os`, `-Ofast`.
// - Try to use IPO [3] by adding `-flto` flag for compiler
//
// And try to uncomment anonymous namespaces in `a.cpp` and `b.cpp` (program should work just fine).
//
// There is also a book "Linkers and Loaders" by John R. Levine [2] where you can reed more on how
// linkers actually work.
//
// [1] http://en.cppreference.com/w/cpp/language/definition#One_Definition_Rule
// [2] https://en.wikipedia.org/wiki/John_R._Levine
// [3] https://en.wikipedia.org/wiki/Interprocedural_optimization

int main() {
    SayHelloTo161_1();
    SayYourNameAndPurpose();
}
