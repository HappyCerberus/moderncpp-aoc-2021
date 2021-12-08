#ifndef WIRING_H_
#define WIRING_H_

#include "display.h"
#include <array>
#include <unordered_map>

using Wiring = std::array<uint8_t, 7>;

inline const std::unordered_map<Display, uint8_t> DECIMALS = {{NUMBERS[0], 0}, {NUMBERS[1], 1}, {NUMBERS[2], 2}, {NUMBERS[3], 3}, {NUMBERS[4], 4},
                                                              {NUMBERS[5], 5}, {NUMBERS[6], 6}, {NUMBERS[7], 7}, {NUMBERS[8], 8}, {NUMBERS[9], 9}};

Wiring solve_wiring(const Puzzle &);
uint32_t decode_number(const Puzzle &, const Wiring &);

#endif