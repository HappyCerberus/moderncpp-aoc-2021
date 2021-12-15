#ifndef CAVE_H_
#define CAVE_H_

#include <cstdint>
#include <iosfwd>
#include <vector>

using Cave = std::vector<std::vector<uint8_t>>;

Cave parse_cave(std::istream &);
Cave expand_cave(const Cave &cave);
size_t least_path_cost(const Cave &);
size_t least_path_cost_fast(const Cave &);

#endif