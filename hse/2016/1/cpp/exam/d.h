#include <iostream>
#include <string>

// https://contest.yandex.ru/contest/3016/problems/D/

class Serializer {
 public:
    virtual ~Serializer() = 0;
    virtual void BeginArray() = 0;
    virtual void AddArrayItem(const std::string&) = 0;
    virtual void EndArray() = 0;
};

Serializer::~Serializer() = default;

class JsonSerializer : public Serializer {
    bool is_first_item_{true};
    std::ostream& out_{std::cout};

 public:
    void BeginArray() override {
        AddComma();
        out_ << '[';
        is_first_item_ = true;
    }

    void AddArrayItem(const std::string& item) override {
        AddComma();
        out_ << '"' << item << '"';
    }

    void EndArray() override {
        is_first_item_ = false;
        out_ << ']';
    }

 private:
    void AddComma() {
        if (!is_first_item_) {
            out_ << ',';
        }
        is_first_item_ = false;
    }
};
