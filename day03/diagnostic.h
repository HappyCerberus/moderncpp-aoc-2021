#ifndef DIAGNOSTIC_H_
#define DIAGNOSTIC_H_

#include <array>
#include <bitset>
#include <cstdint>
#include <iostream>
#include <ranges>
#include <vector>

inline uint32_t div2_roundup(uint32_t v) { return v / 2 + (v & 1); }
inline bool has_bit_set(uint32_t v, uint8_t bit) { return v & (UINT32_C(1) << bit); }

uint32_t gamma_rate(const std::vector<uint32_t> &data, uint8_t width);

template <uint8_t width> uint32_t gamma_rate(std::istream &s) {
  std::array<uint32_t, width> cnt_ones;
  cnt_ones.fill(0);
  uint32_t processed = 0;
  for (auto set : std::ranges::istream_view<std::bitset<width>>(s)) {
    for (uint32_t i = 0; i < width; i++) {
      cnt_ones[i] += set[i];
    }
    processed++;
  }
  uint32_t result = 0;
  for (int32_t i = width - 1; i >= 0; i--) {
    result = (result << 1) | (cnt_ones[i] >= div2_roundup(processed));
  }
  return result;
}

uint32_t epsilon_rate(uint32_t gamma_rate, uint8_t width);

#endif