#include "h.h"

#include <iostream>

// namespace {
struct IAmAboutToViolateODR {
    int x{0XBA461};
};
// }

void SayHelloTo161_1() {
    IAmAboutToViolateODR sup;
    std::cout << "Hello, 161-" << sup.x << std::endl;
}
