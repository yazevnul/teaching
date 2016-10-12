#include <array>
#include <iostream>
#include <iterator>
#include <list>
#include <set>
#include <vector>

// Iterator over container of containers [1]
//
// [1] https://contest.yandex.ru/contest/2936/problems/E/

template <typename T>
class TransparentIterator : std::iterator<
                                std::forward_iterator_tag,
                                const typename T::value_type::value_type>
{
    using base = std::iterator<std::forward_iterator_tag, const typename T::value_type::value_type>;
    using row_iterator = typename T::const_iterator;
    using column_iterator_iterator = typename T::value_type::const_iterator;

    bool is_end_{true};
    row_iterator cur_row_;
    row_iterator end_row_;
    column_iterator_iterator cur_;
    column_iterator_iterator end_;

    void roll_forward() {
        while (!is_end_) {
            if (cur_ == end_) {
                if (!(is_end_ = (++cur_row_ == end_row_))) {
                    if ((cur_ = cur_row_->begin()) != (end_ = cur_row_->end())) {
                        break;
                    }
                }
            } else {
                if (!(++cur_ == end_)) {
                    break;
                }
            }
        }
    }

public:
    TransparentIterator() = default;
    TransparentIterator(const T& data)
        : cur_row_{data.begin()}
        , end_row_{data.end()} {

        if (!(is_end_ = cur_row_ == end_row_)) {
            if ((cur_ = cur_row_->begin()) == (end_ = cur_row_->end())) {
                roll_forward();
            }
        }
    }

    TransparentIterator& operator++() {
        roll_forward();
        return *this;
    }

    TransparentIterator operator++(int) {
        TransparentIterator rv{*this};
        ++(*this);
        return rv;
    }

    bool operator==(const TransparentIterator& other) const {
        if (is_end_ != other.is_end_) {
            return false;
        }
        if (is_end_) {
            return true;
        }
        if (cur_row_ != other.cur_row_) {
            return false;
        }
        return cur_ == other.cur_;
    }

    bool operator!=(const TransparentIterator& other) const {
        return !operator==(other);
    }

    typename base::reference operator*() const {
        return *cur_;
    }
};

template <typename T>
class TransparentIteratorRange {
    TransparentIterator<const T> begin_;
    TransparentIterator<const T> end_;

public:
    explicit TransparentIteratorRange(const T& data)
        : begin_{data} {
    }

    TransparentIterator<const T> begin() const {
        return begin_;
    }

    TransparentIterator<const T> end() const {
        return end_;
    }
};

template <typename T>
TransparentIteratorRange<T> MakeRange(const T& data) {
    return TransparentIteratorRange<T>(data);
}

int main() {
    {
        std::cout << "-----empty-----" << '\n';
        std::vector<std::vector<int>> v;
        for (const auto x : MakeRange(v)) {
            std::cout << x << ' ';
        }
        std::cout << '\n';
        std::cout << "-----empty-----" << '\n';
    }
    {
        std::cout << "-----one-----" << '\n';
        std::vector<std::vector<int>> v = {{1, 2, 3}};
        for (const auto x : MakeRange(v)) {
            std::cout << x << ' ';
        }
        std::cout << '\n';
        std::cout << "-----one-----" << '\n';
    }
    {
        std::cout << "-----two-----" << '\n';
        std::vector<std::vector<int>> v = {{1, 2, 3}, {4, 5, 6, 7}};
        for (const auto x : MakeRange(v)) {
            std::cout << x << ' ';
        }
        std::cout << '\n';
        std::cout << "-----two-----" << '\n';
    }
    {
        std::cout << "-----three-----" << '\n';
        std::vector<std::vector<int>> v = {{1, 2, 3}, {}, {4, 5, 6, 7}};
        for (const auto x : MakeRange(v)) {
            std::cout << x << ' ';
        }
        std::cout << '\n';
        std::cout << "-----three-----" << '\n';
    }
    {
        std::cout << "-----five-----" << '\n';
        std::vector<std::vector<int>> v = {{}, {}, {}};
        for (const auto x : MakeRange(v)) {
            std::cout << x << ' ';
        }
        std::cout << '\n';
        std::cout << "-----five-----" << '\n';
    }
    {
        std::cout << "-----six-----" << '\n';
        std::vector<std::vector<int>> v = {{}, {}, {}, {1, 2, 3}, {4, 5, 6, 7}};
        for (const auto x : MakeRange(v)) {
            std::cout << x << ' ';
        }
        std::cout << '\n';
        std::cout << "-----six-----" << '\n';
    }
    {
        std::cout << "-----seven-----" << '\n';
        std::vector<std::array<int, 4>> v = {{}, {}, {}, {{1, 2, 3}}, {{4, 5, 6, 7}}};
        for (const auto x : MakeRange(v)) {
            std::cout << x << ' ';
        }
        std::cout << '\n';
        std::cout << "-----seven-----" << '\n';
    }
    {
        std::cout << "-----eight-----" << '\n';
        std::vector<std::set<int>> v = {{}, {}, {}, {{1, 2, 3}}, {{4, 5, 6, 7}}};
        for (const auto x : MakeRange(v)) {
            std::cout << x << ' ';
        }
        std::cout << '\n';
        std::cout << "-----eight-----" << '\n';
    }
    {
        std::cout << "-----nine-----" << '\n';
        std::list<std::set<int>> v = {{}, {}, {}, {{1, 2, 3}}, {{4, 5, 6, 7}}};
        for (const auto x : MakeRange(v)) {
            std::cout << x << ' ';
        }
        std::cout << '\n';
        std::cout << "-----nine-----" << '\n';
    }
}

