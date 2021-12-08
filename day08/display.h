#ifndef DISPLAY_H_
#define DISPLAY_H_

#include <array>
#include <cstdint>
#include <vector>

using Display = uint8_t;

constexpr const Display SEGMENT_A = 1;
constexpr const Display SEGMENT_B = 1 << 1;
constexpr const Display SEGMENT_C = 1 << 2;
constexpr const Display SEGMENT_D = 1 << 3;
constexpr const Display SEGMENT_E = 1 << 4;
constexpr const Display SEGMENT_F = 1 << 5;
constexpr const Display SEGMENT_G = 1 << 6;

constexpr const std::array<Display, 10> NUMBERS = {
    SEGMENT_A | SEGMENT_B | SEGMENT_C | SEGMENT_E | SEGMENT_F | SEGMENT_G,             // 0
    SEGMENT_C | SEGMENT_F,                                                             // 1
    SEGMENT_A | SEGMENT_C | SEGMENT_D | SEGMENT_E | SEGMENT_G,                         // 2
    SEGMENT_A | SEGMENT_C | SEGMENT_D | SEGMENT_F | SEGMENT_G,                         // 3
    SEGMENT_B | SEGMENT_C | SEGMENT_D | SEGMENT_F,                                     // 4
    SEGMENT_A | SEGMENT_B | SEGMENT_D | SEGMENT_F | SEGMENT_G,                         // 5
    SEGMENT_A | SEGMENT_B | SEGMENT_D | SEGMENT_E | SEGMENT_F | SEGMENT_G,             // 6
    SEGMENT_A | SEGMENT_C | SEGMENT_F,                                                 // 7
    SEGMENT_A | SEGMENT_B | SEGMENT_C | SEGMENT_D | SEGMENT_E | SEGMENT_F | SEGMENT_G, // 8
    SEGMENT_A | SEGMENT_B | SEGMENT_C | SEGMENT_D | SEGMENT_F | SEGMENT_G,             // 9
};

struct Puzzle {
  std::vector<Display> patterns;
  std::vector<Display> numbers;
};

uint8_t cnt_segments(Display display);

#endif