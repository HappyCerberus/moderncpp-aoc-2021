#ifndef SEABED_H_
#define SEABED_H_

#include <cstdint>
#include <iosfwd>
#include <unordered_map>
#include <vector>

using SeaBed = std::vector<std::vector<char>>;

SeaBed parse_seabed(std::istream &);
std::pair<SeaBed, size_t> tick(const SeaBed &);

std::ostream &operator<<(std::ostream &, const SeaBed &);

#endif