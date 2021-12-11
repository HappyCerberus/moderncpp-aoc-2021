// increase everything by 1, if the element is over 9, add to unordered_set
// while stack not empty, take element from unordered_set, set it to -1
// add 1 to surrounding, if they are over 9, add to unordered_set

#include "flashing.h"

#include <algorithm>
#include <istream>
#include <unordered_set>

Cavern parse_cavern(std::istream &input) {
  Cavern result;
  std::vector<uint8_t> line;
  char c;

  input.unsetf(std::ios_base::skipws);
  while (input >> c) {
    if (c == '\n') {
      result.emplace_back(move(line));
    } else if (std::isdigit(c)) {
      line.push_back(c - '0');
    }
  }
  if (line.size() > 0)
    result.emplace_back(std::move(line));

  return result;
}

uint32_t tick(Cavern &cave) {
  uint32_t total = 0;
  std::unordered_set<size_t> pending;

  for (size_t row = 0; row < cave.size(); row++) {
    for (size_t column = 0; column < cave[row].size(); column++) {
      cave[row][column]++;
      if (cave[row][column] > 9)
        pending.insert(row * cave.size() + column);
    }
  }

  while (pending.size() > 0) {
    auto el = pending.begin();
    pending.erase(*el);
    ssize_t row = (*el) / cave.size();
    ssize_t col = (*el) % cave.size();
    cave[row][col] = 0;
    total++;
    for (ssize_t ri = row - 1; ri <= row + 1; ri++) {
      for (ssize_t ci = col - 1; ci <= col + 1; ci++) {
        if (ri < 0 || ci < 0 || ri >= std::ranges::ssize(cave) || ci >= std::ranges::ssize(cave))
          continue;
        if (cave[ri][ci] != 0)
          cave[ri][ci]++;
        if (cave[ri][ci] > 9)
          pending.insert(ri * cave.size() + ci);
      }
    }
  }

  return total;
}
