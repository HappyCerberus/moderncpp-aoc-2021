#include "heightmap.h"

#include <istream>

HeightMap read_heightmap(std::istream &s) {
  HeightMap result;
  std::vector<uint8_t> line;
  char c;

  s.unsetf(std::ios_base::skipws);
  while (s >> c) {
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

bool is_low_point(HeightMap &map, size_t row, size_t column) {
  if (row >= map.size() || column >= map[row].size())
    throw std::out_of_range("Indices out of range of map.");
  uint8_t v = map[row][column];
  if (row != 0 && map[row - 1][column] <= v)
    return false;
  if (column != 0 && map[row][column - 1] <= v)
    return false;
  if (row + 1 < map.size() && map[row + 1][column] <= v)
    return false;
  if (column + 1 < map[0].size() && map[row][column + 1] <= v)
    return false;
  return true;
}