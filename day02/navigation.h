#ifndef NAVIGATION_H_
#define NAVIGATION_H_

#include <cstdint>
#include <iosfwd>
#include <string>

struct Position {
  int32_t depth;
  int32_t distance;
  friend auto operator<=>(const Position &, const Position &) = default;
  Position &operator+=(const Position &other) {
    depth += other.depth;
    distance += other.distance;
    return *this;
  };
};

Position navigate(std::istream &s);

Position navigate(const std::string &line);

#endif