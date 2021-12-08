#include "wiring.h"
#include "display.h"

#include <bit>

bool segment_lit(Display disp, uint8_t segment) { return disp & (1 << segment); }

Wiring solve_wiring(const Puzzle &input) {
  Wiring result = {NUMBERS[8], NUMBERS[8], NUMBERS[8], NUMBERS[8], NUMBERS[8], NUMBERS[8], NUMBERS[8]};
  for (auto pattern : input.patterns) {
    switch (cnt_segments(pattern)) {
    case 2:
      for (uint8_t wire_in = 0; wire_in < 7; wire_in++) {
        if (segment_lit(pattern, wire_in)) {
          result[wire_in] &= (SEGMENT_C | SEGMENT_F);
        } else {
          result[wire_in] &= ~(SEGMENT_C | SEGMENT_F);
        }
      }
      break;
    case 3:
      for (uint8_t wire_in = 0; wire_in < 7; wire_in++) {
        if (segment_lit(pattern, wire_in)) {
          result[wire_in] &= (SEGMENT_A | SEGMENT_C | SEGMENT_F);
        } else {
          result[wire_in] &= ~(SEGMENT_A | SEGMENT_C | SEGMENT_F);
        }
      }
      break;
    case 4:
      for (uint8_t wire_in = 0; wire_in < 7; wire_in++) {
        if (segment_lit(pattern, wire_in)) {
          result[wire_in] &= (SEGMENT_B | SEGMENT_C | SEGMENT_D | SEGMENT_F);
        } else {
          result[wire_in] &= ~(SEGMENT_B | SEGMENT_C | SEGMENT_D | SEGMENT_F);
        }
      }
      break;
    case 5:
      for (uint8_t wire_in = 0; wire_in < 7; wire_in++) {
        if (!segment_lit(pattern, wire_in)) {
          result[wire_in] &= (SEGMENT_B | SEGMENT_C | SEGMENT_E | SEGMENT_F);
        }
      }
      break;
    case 6:
      for (uint8_t wire_in = 0; wire_in < 7; wire_in++) {
        if (!segment_lit(pattern, wire_in)) {
          result[wire_in] &= (SEGMENT_C | SEGMENT_D | SEGMENT_E);
        }
      }
      break;
    }
  }
  for (auto singular_wire : result) {
    if (std::popcount(singular_wire) != 1)
      continue;

    for (auto &undecided_wire : result) {
      if (std::popcount(undecided_wire) == 1)
        continue;
      undecided_wire &= ~singular_wire;
    }
  }
  return result;
}

uint32_t decode_number(const Puzzle &puzzle, const Wiring &solved_wiring) {
  uint32_t result = 0;
  for (auto digit : puzzle.numbers) {
    uint8_t display = 0;
    for (uint8_t bit = 0; bit < 7; bit++) {
      if (segment_lit(digit, bit))
        display |= solved_wiring[bit];
    }

    result *= 10;
    result += DECIMALS.at(display);
  }
  return result;
}