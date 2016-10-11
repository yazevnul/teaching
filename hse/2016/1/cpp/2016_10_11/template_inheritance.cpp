#include <iostream>

// https://en.wikipedia.org/wiki/Curiously_recurring_template_pattern

template <typename T>
class OneWhoMakeOthersTalk {
protected:
    virtual void DoTalk(std::ostream& out) const = 0;

public:
    virtual ~OneWhoMakeOthersTalk() = default;

    void Talk(std::ostream& out) const {
        DoTalk(out);
    }
};

class Introvert : public OneWhoMakeOthersTalk<Introvert> {
protected:
    void DoTalk(std::ostream& out) const override {
        out << "sup" << std::endl;
    }
};

int main() {
    Introvert introvert;
    introvert.Talk(std::cout);
}
