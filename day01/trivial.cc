#include "trivial.h"

#include <algorithm>
#include <istream>
#include <limits>
#include <ranges>
#include <utility>

uint32_t count_increasing(std::istream &input) {
  return std::ranges::count_if(std::ranges::istream_view<uint32_t>(input),
                               [prev = std::numeric_limits<uint32_t>::max()](uint32_t curr) mutable { return std::exchange(prev, curr) < curr; });
}