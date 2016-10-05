#include "h.h"

#include <iostream>
#include <string>

// namespace {
struct IAmAboutToViolateODR {
    std::string name{"Tron"};
    std::string purpose{"Fight for the Users"};
};
// }

void SayYourNameAndPurpose() {
    IAmAboutToViolateODR sup;
    std::cout << "name: \"" << sup.name << "\" purpose: \"" << sup.purpose << '"' << std::endl;
}
