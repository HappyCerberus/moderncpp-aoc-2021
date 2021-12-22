#ifndef RANGE_H_
#define RANGE_H_

#include "point.h"

#include <optional>
#include <string>

struct CuboidInstruction {
  Point3D min;
  Point3D max;
  bool on;
  operator int64_t() const;
  friend std::istream &operator>>(std::istream &, CuboidInstruction &);
  friend std::ostream &operator<<(std::ostream &, const CuboidInstruction &);
  friend auto operator<=>(const CuboidInstruction &, const CuboidInstruction &) = default;
};

std::optional<CuboidInstruction> intersect(const CuboidInstruction &, const CuboidInstruction &);

int64_t apply_instructions(std::istream &, std::optional<CuboidInstruction>);

#endif