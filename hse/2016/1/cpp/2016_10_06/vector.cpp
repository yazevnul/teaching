#include <vector>
#include <iostream>
#include <iterator>
#include <initializer_list>

template <typename T>
class Vector {
    std::vector<T> data_;

public:
    class const_iterator;
    class iterator : public std::iterator<
                         std::forward_iterator_tag,
                         T>
    {
        std::vector<T>* data_{nullptr};
        size_t index_{0};

        friend class const_iterator;
    public:
        iterator(
            std::vector<T>& data,
            const size_t index)
            : data_{&data}
            , index_{index} {
        }

        iterator& operator++() {
            ++index_;
            return *this;
        }

        iterator operator++(int) {
            iterator rv{*this};
            ++(*this);
            return rv;
        }

        bool operator == (iterator other) const {
            return index_ == other.index_;
        }

        bool operator != (iterator other) const {
            return !operator==(other);
        }

        typename std::iterator<
            std::forward_iterator_tag,
            T>::reference
        operator*() const {
            return data_->operator[](index_);
        }
    };

    class const_iterator : public std::iterator<
                         std::forward_iterator_tag,
                         const T>
    {
        const std::vector<T>* data_{nullptr};
        size_t index_{0};
    public:
        const_iterator(
            const std::vector<T>& data,
            const size_t index)
            : data_{&data}
            , index_{index} {
        }

        const_iterator(
            const iterator other)
            : data_{other.data_}
            , index_{other.index_} {
        }

        const_iterator& operator++() {
            ++index_;
            return *this;
        }

        const_iterator operator++(int) {
            iterator rv{*this};
            ++(*this);
            return rv;
        }

        bool operator == (const_iterator other) const {
            return index_ == other.index_;
        }

        bool operator != (const_iterator other) const {
            return !operator==(other);
        }

        typename std::iterator<
            std::forward_iterator_tag,
            const T>::reference
        operator*() const {
            return data_->at(index_);
        }
    };

    explicit Vector(const size_t size)
        : data_(size) {
    }

    Vector(const std::initializer_list<T> init)
        : data_(init) {
    }

    T& operator[](const size_t index) {
        return data_[index];
    }

    const T& operator[](const size_t index) const {
        return data_[index];
    }

    size_t size() const {
        return data_.size();
    }

    iterator begin() {
        return {data_, size_t{}};
    }

    iterator end() {
        return {data_, data_.size()};
    }

    const_iterator begin() const {
        return {data_, size_t{}};
    }

    const_iterator end() const {
        return {data_, data_.size()};
    }

    const_iterator cbegin() const {
        return {data_, size_t{}};
    }

    const_iterator cend() const {
        return {data_, data_.size()};
    }
};

template <typename T>
std::ostream& operator <<(std::ostream& out, const Vector<T>& v) {
    out << '(';
    for (size_t i = 0, i_end = v.size(); i < i_end; ++i) {
        if (i) {
            out << ',';
        }
        out << v[i];
    }
    out << ')';
    return out;
}

int main() {
    {
        const Vector<float> v = {1.f, 2.f, 3.f};
        std::cout << v << std::endl;

        for (const auto x : v) {
            std::cout << x << std::endl;
        }
    }
    {
        Vector<float> v = {1.f, 2.f, 3.f};
        std::cout << v << std::endl;

        for (auto& x : v) {
            x = 6.f;
        }
        std::cout << v << std::endl;
    }
}
