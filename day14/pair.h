#ifndef PAIR_H_
#define PAIR_H_

#include <functional>

struct Pair {
  char first;
  char second;
  friend auto operator<=>(const Pair &, const Pair &) = default;
};

template <> struct std::hash<Pair> {
  std::size_t operator()(Pair const &s) const noexcept {
    std::size_t h1 = std::hash<char>{}(s.first);
    std::size_t h2 = std::hash<char>{}(s.second);
    return h1 ^ (h2 << 1); // or use boost::hash_combine
  }
};

#endif