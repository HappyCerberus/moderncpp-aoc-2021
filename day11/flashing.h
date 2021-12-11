#ifndef FLASHING_H_
#define FLASHING_H_

#include <cstdint>
#include <iosfwd>
#include <vector>

using Cavern = std::vector<std::vector<uint8_t>>;

Cavern parse_cavern(std::istream &);
uint32_t tick(Cavern &);

#endif
