#include "display.h"
#include <algorithm>
#include <bit>

uint8_t cnt_segments(Display display) { return std::popcount(display); }