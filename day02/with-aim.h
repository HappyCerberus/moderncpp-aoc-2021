#ifndef WITH_AIM_H_
#define WITH_AIM_H_

#include <cstdint>
#include <iosfwd>
#include <string>

struct Position {
  int32_t depth;
  int32_t distance;
  int32_t aim;

  Position &forward(int32_t magnitude) {
    distance += magnitude;
    depth += aim * magnitude;
    return *this;
  }
  Position &up(int32_t magnitude) {
    aim -= magnitude;
    return *this;
  }
  Position &down(int32_t magnitude) {
    aim += magnitude;
    return *this;
  }

  friend auto operator<=>(const Position &, const Position &) = default;
};

Position navigate(std::istream &s);

void navigate(Position &pos, const std::string &line);

#endif