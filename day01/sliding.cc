#include "sliding.h"

#include <algorithm>
#include <iostream>
#include <istream>
#include <limits>
#include <ranges>
#include <utility>

/* ranges & views
uint32_t count_increasing_windows(std::istream &input) {
  auto sliding_window_view = std::ranges::istream_view<uint32_t>(input) | std::ranges::views::transform([e1 = 0, e2 = 0, e3 = 0](uint32_t curr) mutable {
                               e1 = std::exchange(e2, std::exchange(e3, curr));
                               return e1 + e2 + e3;
                             });

  return std::ranges::count_if(sliding_window_view, [prev = std::numeric_limits<uint32_t>::max(), drop = 2](uint32_t curr) mutable {
    if (drop > 0) {
      drop--;
      return false;
    }
    return std::exchange(prev, curr) < curr;
  });
}*/

uint32_t count_increasing_windows(std::istream &input) {
  uint32_t e1 = 0, e2 = 0, e3 = 0, prev_sum = std::numeric_limits<uint32_t>::max(), drop = 2, cnt = 0;
  for (uint32_t v : std::ranges::istream_view<uint32_t>(input)) {
    e1 = std::exchange(e2, std::exchange(e3, v));
    if (drop > 0) {
      drop--;
      continue;
    }
    if (std::exchange(prev_sum, e1 + e2 + e3) < e1 + e2 + e3)
      cnt++;
  }
  return cnt;
}
