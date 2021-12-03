#include "diagnostic.h"

#include <algorithm>
#include <istream>

uint32_t epsilon_rate(uint32_t gamma_rate, uint8_t width) {
  uint32_t mask = ~(UINT32_MAX << width);
  return (~gamma_rate) & mask;
}

uint32_t gamma_rate(const std::vector<uint32_t> &data, uint8_t width) {
  uint32_t result = 0;
  for (int8_t i = width - 1; i >= 0; i--) {
    uint32_t cnt_one = std::ranges::count_if(data, [i](auto v) { return has_bit_set(v, i); });
    result = (result << 1) | (cnt_one >= div2_roundup(data.size()));
  }
  return result;
}
