#include <iostream>
#include <memory>
#include <typeinfo>

#include <cinttypes>

// Factory pattern [1]
//
// [1] https://en.wikipedia.org/wiki/Abstract_factory_pattern

class IAnimal {
public:
    virtual ~IAnimal() = 0;
    virtual void Say(std::ostream& out) const = 0;
};

IAnimal::~IAnimal() {
}

class Cat : public IAnimal {
public:
    void Say(std::ostream& out) const override {
        out << "meow" << std::endl;
    }
};

class Dog : public IAnimal {
public:
    void Say(std::ostream& out) const override {
        out << "bark" << std::endl;
    }
};

class Fish : public IAnimal {
public:
    void Say(std::ostream& out) const override {
        out << "..." << std::endl;
    }
};

class Cow : public IAnimal {
public:
    void Say(std::ostream& out) const override {
        out << "moo" << std::endl;
    }
};

// http://en.cppreference.com/w/cpp/language/enum
enum class EAnimal : uint32_t {
    No = 0,
    Cat = 1,
    Dog = 2,
    Fish = 3,
    Cow = 4
};

static std::unique_ptr<IAnimal> MakeAnimal(const EAnimal type) {
    switch (type) {
        case EAnimal::Cat:
            return std::make_unique<Cat>();
        case EAnimal::Dog:
            return std::make_unique<Dog>();
        case EAnimal::Fish:
            return std::make_unique<Fish>();
        case EAnimal::Cow:
            return std::make_unique<Cow>();
        case EAnimal::No:
            return nullptr;
    };
}

static EAnimal ToEnum(const std::string& name) {
    static const char* names[] = {"cat", "dog", "fish", "cow"};
    for (size_t i = 0; i < 4; ++i) {
        if (names[i] == name) {
            return static_cast<EAnimal>(i + 1);
        }
    }
    return EAnimal::No;
}

int main() {
    for (std::string line; getline(std::cin, line);) {
        const auto animal = MakeAnimal(ToEnum(line));
        if (animal) {
            animal->Say(std::cout);
        }
    }
}
