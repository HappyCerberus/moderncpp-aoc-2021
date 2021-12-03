#ifndef RATINGS_H_
#define RATINGS_H_

#include <algorithm>
#include <bitset>
#include <iostream>
#include <vector>

struct Ratings {
  uint32_t oxygen_generator;
  uint32_t co2_scrubber;
  friend auto operator<=>(const Ratings &, const Ratings &) = default;
  friend std::ostream &operator<<(std::ostream &s, const Ratings &r) {
    s << r.oxygen_generator << " - " << r.co2_scrubber;
    return s;
  }
};

uint32_t find_oxygen_rating(auto begin, auto end, int index) {
  if (end - begin == 1 || index == -1) {
    return begin->to_ulong();
  }
  auto pp = std::partition(begin, end, [index](auto &v) { return v[index] == 1; });
  if (std::distance(begin, pp) >= std::distance(pp, end)) {
    return find_oxygen_rating(begin, pp, index - 1);
  } else {
    return find_oxygen_rating(pp, end, index - 1);
  }
}

uint32_t find_co2_rating(auto begin, auto end, int index) {
  if (end - begin == 1 || index == -1) {
    return begin->to_ulong();
  }
  auto pp = std::partition(begin, end, [index](auto &v) { return v[index] == 1; });
  if (std::distance(begin, pp) < std::distance(pp, end) || pp == end) {
    return find_co2_rating(begin, pp, index - 1);
  } else {
    return find_co2_rating(pp, end, index - 1);
  }
}

template <uint32_t width> Ratings find_rating(std::vector<std::bitset<width>> &data) {
  auto pp = std::partition(data.begin(), data.end(), [](auto &v) { return v[width - 1] == 1; });
  if (pp == data.end()) {
    return {.oxygen_generator = find_oxygen_rating(data.begin(), data.end(), width - 2), .co2_scrubber = find_co2_rating(data.begin(), data.end(), width - 2)};
  } else if (std::distance(data.begin(), pp) >= std::distance(pp, data.end())) {
    return {.oxygen_generator = find_oxygen_rating(data.begin(), pp, width - 2), .co2_scrubber = find_co2_rating(pp, data.end(), width - 2)};
  } else {
    return {.oxygen_generator = find_oxygen_rating(pp, data.end(), width - 2), .co2_scrubber = find_co2_rating(data.begin(), pp, width - 2)};
  }
}

#endif