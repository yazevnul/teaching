#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include <unordered_set>
#include <vector>

// https://contest.yandex.ru/contest/3016/problems/B/

static std::vector<std::string> Split(const std::string& str, const char delimiter) {
    std::vector<std::string> parts{{}};
    for (const auto c : str) {
        if (delimiter == c) {
            parts.emplace_back();
        } else {
            parts.back() += c;
        }
    }
    return parts;
}

template <typename It>
static std::string Join(const It begin, const It end, const char delimiter) {
    std::string joined;
    for (auto it = begin; end != it; ++it) {
        if (begin != it) {
            joined += delimiter;
        }
        joined += *it;
    }
    return joined;
}

static std::vector<std::string> Sort(const std::unordered_set<std::string>& data) {
    std::vector<std::string> sorted{begin(data), end(data)};
    std::sort(begin(sorted), end(sorted));
    return sorted;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cin.tie(nullptr);

    std::unordered_set<std::string> directories;
    for (std::string path; getline(std::cin, path);) {
        const auto parts = Split(path, '/');
        for (auto it = std::next(std::begin(parts)), it_end = std::end(parts); it != it_end; ++it) {
            directories.insert(Join(std::begin(parts), it, '/') + '/');
        }
    }
    for (const auto& dir : Sort(directories)) {
        std::cout << dir << '\n';
    }
}
