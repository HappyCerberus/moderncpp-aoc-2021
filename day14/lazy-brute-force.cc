#include "lazy-brute-force.h"
#include <utility>

Generator<char> polymer_expander(std::string base) {
  for (auto c : base)
    co_yield c;
}

Generator<char> polymer_expander(InsertionRules &rules, Generator<char> base) {
  Pair pair = {'\0', '\0'};
  for (auto c : base) {
    pair.first = std::exchange(pair.second, c);
    if (pair.first != '\0')
      co_yield pair.first;
    if (rules.contains(pair))
      co_yield rules[pair];
  }
  co_yield pair.second;
}
