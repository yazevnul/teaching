#include <iostream>

// Basic example of C++ inheritance [1]. There are 6 types of inheritance:
// `public`, `private`, `protected`, `virtual public`, `virtual private` and `virtual protected`.
//
// But most of the time you need `public` inheritance.
//
// Rules of thumb:
// - want to use inheritance -> dtor must be virtual
// - want to override class method? -> mark method with `override` keyword
// - never call virtual method in dtor or ctor
//
// [1] http://en.cppreference.com/w/cpp/language/derived_class

class IAnimal {
public:
    virtual ~IAnimal()  = 0;
    virtual void Say(std::ostream& out) const = 0;
};

IAnimal::~IAnimal() {
        std::cout << "IAnimal dtor" << std::endl;
}

class IMammal : public IAnimal {
public:
    ~IMammal() override = 0;
    void Say(std::ostream& out) const override {
        out << "don't know what to say, I'm just a mammal!" << std::endl;
    }
};

IMammal::~IMammal() {
    std::cout << "IMammal dtor" << std::endl;
}

class Cat : public IMammal {
public:
    Cat() {
        std::cout << "Cat ctor" << std::endl;
    }
    ~Cat() override {
        std::cout << "Cat dtor" << std::endl;
    }
    void Say(std::ostream& out) const override {
        out << "meow" << std::endl;
    }
};

static void Say(const IAnimal& animal) {
    animal.Say(std::cout);
}

int main() {
    Cat cat;
    Say(cat);

    // IMammal mammal;
    // Say(mammal);
}
