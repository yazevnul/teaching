#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include <unordered_map>

// https://contest.yandex.ru/contest/3016/problems/A/

static std::unordered_map<char, char> ReadMapping(std::istream &in) {
  std::string from;
  std::string to;
  std::getline(in, from);
  std::getline(in, to);

  std::unordered_map<char, char> mapping;
  mapping.reserve(from.size());
  for (size_t i = 0, i_end = from.size(); i < i_end; ++i) {
    mapping.insert({from[i], to[i]});
  }
  return mapping;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  // http://en.cppreference.com/w/cpp/iterator/istreambuf_iterator
  // http://en.cppreference.com/w/cpp/iterator/ostreambuf_iterator
  const auto mapping = ReadMapping(std::cin);
  std::transform(
    std::istreambuf_iterator<char>{std::cin}, std::istreambuf_iterator<char>{},
    std::ostreambuf_iterator<char>{std::cout},
    [&mapping](const char c) {
      const auto it = mapping.find(c);
      if (std::end(mapping) != it) {
        return it->second;
      }
      return c;
    });
}
