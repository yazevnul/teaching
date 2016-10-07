#include <iostream>
#include <iterator>
#include <vector>
#include <list>

template <typename It, typename Tag = typename std::iterator_traits<It>::iterator_category>
struct DistanceImpl {
    size_t operator()(It from, It to) const {
        size_t dist = 0;
        for (; from != to; ++from, (void)++dist) {
        }
        return dist;
    }
};

template <typename It>
struct DistanceImpl<It, std::random_access_iterator_tag> {
    size_t operator()(It from, It to) const {
        return to - from;
    }
};

template <typename It>
size_t my_distance(It from, It to) {
    return DistanceImpl<It>()(from, to);
}

int main() {
    std::vector<int> x(10);
    std::list<int> l;
    l.push_back(1);
    l.push_back(2);
    l.push_back(3);
    l.push_back(4);
    l.push_back(5);
    l.push_back(6);

    std::cout << my_distance(x.begin(), x.end()) << std::endl;
    std::cout << my_distance(l.begin(), l.end()) << std::endl;
}
