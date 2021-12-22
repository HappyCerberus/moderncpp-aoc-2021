#include "range.h"

#include <algorithm>
#include <iostream>
#include <istream>
#include <numeric>
#include <ostream>
#include <ranges>
#include <stdexcept>
#include <string>

std::istream &operator>>(std::istream &s, CuboidInstruction &cube) {
  std::string line;
  if (!getline(s, line))
    return s;

  CuboidInstruction result;
  if (line.starts_with("on")) {
    result.on = true;
  } else if (line.starts_with("off")) {
    result.on = false;
  } else {
    throw std::runtime_error("Failed to parse input. No leading \"on\"/\"off\" found.");
  }

  auto xpos = line.find("x=");
  if (xpos == std::string::npos)
    throw std::runtime_error("Failed to parsed input, did not find x coordinate.");
  result.min.x = std::stoll(line.substr(xpos + 2));
  auto xpos_max = line.find("..", xpos + 2);
  if (xpos_max == std::string::npos)
    throw std::runtime_error("Failed to parsed input, did not find end of x coordinate.");
  result.max.x = std::stoll(line.substr(xpos_max + 2));

  auto ypos = line.find("y=");
  if (ypos == std::string::npos)
    throw std::runtime_error("Failed to parsed input, did not find y coordinate.");
  result.min.y = std::stoll(line.substr(ypos + 2));
  auto ypos_max = line.find("..", ypos + 2);
  if (ypos_max == std::string::npos)
    throw std::runtime_error("Failed to parsed input, did not find end of x coordinate.");
  result.max.y = std::stoll(line.substr(ypos_max + 2));

  auto zpos = line.find("z=");
  if (zpos == std::string::npos)
    throw std::runtime_error("Failed to parsed input, did not find z coordinate.");
  result.min.z = std::stoll(line.substr(zpos + 2));
  auto zpos_max = line.find("..", zpos + 2);
  if (zpos_max == std::string::npos)
    throw std::runtime_error("Failed to parsed input, did not find end of x coordinate.");
  result.max.z = std::stoll(line.substr(zpos_max + 2));

  cube = result;

  return s;
}

std::ostream &operator<<(std::ostream &s, const CuboidInstruction &c) {

  s << (c.on ? "on" : "off");
  s << " x=" << c.min.x << ".." << c.max.x;
  s << " y=" << c.min.y << ".." << c.max.y;
  s << " z=" << c.min.z << ".." << c.max.z;

  return s;
}

std::optional<CuboidInstruction> intersect(const CuboidInstruction &lhs, const CuboidInstruction &rhs) {
  int64_t min_x = std::max(lhs.min.x, rhs.min.x);
  int64_t max_x = std::min(lhs.max.x, rhs.max.x);
  int64_t min_y = std::max(lhs.min.y, rhs.min.y);
  int64_t max_y = std::min(lhs.max.y, rhs.max.y);
  int64_t min_z = std::max(lhs.min.z, rhs.min.z);
  int64_t max_z = std::min(lhs.max.z, rhs.max.z);
  if (min_x > max_x || min_y > max_y || min_z > max_z)
    return {};
  return CuboidInstruction{{min_x, min_y, min_z}, {max_x, max_y, max_z}, !lhs.on};
}

CuboidInstruction::operator int64_t() const {
  if (on) {
    return (max.x - min.x + 1) * (max.y - min.y + 1) * (max.z - min.z + 1);
  } else {
    return -1 * (max.x - min.x + 1) * (max.y - min.y + 1) * (max.z - min.z + 1);
  }
}

int64_t apply_instructions(std::istream &s, std::optional<CuboidInstruction> limit) {
  std::string line;
  std::vector<CuboidInstruction> cuboids;
  CuboidInstruction cube;
  while (s >> cube) {
    if (limit.has_value()) {
      auto smaller = intersect(cube, limit.value());
      if (smaller.has_value())
        cube = smaller.value();
      else
        continue;
    }

    std::vector<CuboidInstruction> merge;
    if (cube.on)
      merge.push_back(cube);
    for (auto &c : cuboids) {
      auto inter = intersect(c, cube);
      if (inter.has_value())
        merge.push_back(inter.value());
    }
    std::ranges::copy(merge, std::back_insert_iterator(cuboids));
  }

  return std::accumulate(cuboids.begin(), cuboids.end(), INT64_C(0), std::plus<>());
}