#ifndef HEIGHTMAP_H_
#define HEIGHTMAP_H_

#include <cstdint>
#include <iosfwd>
#include <vector>

using HeightMap = std::vector<std::vector<uint8_t>>;

HeightMap read_heightmap(std::istream &);
bool is_low_point(HeightMap &map, size_t row, size_t column);

#endif