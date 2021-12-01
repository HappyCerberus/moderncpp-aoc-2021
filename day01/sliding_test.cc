#include "sliding.h"

#include <gtest/gtest.h>
#include <sstream>

TEST(SlidingTest, Simple)
{
    std::vector<std::pair<std::string, uint32_t>> inputs = {
        {"", 0},                                        // not enough elements for a window
        {"0 1", 0},                                     // not enough elements for a window
        {"0 1 0", 0},                                   // a single window
        {"0 0 0 0 0 0", 0},                             // monotonic, no increase
        {"0 1 2 3", 1},                                 // two windows, increasing
        {"3 2 1 0", 0},                                 // two windows, decreasing
        {"0 1 0 1 0 1", 2},                             // 1, 2, 1, 2 - two increasing
        {"199 200 208 210 200 207 240 269 260 263", 5}, // from aoc
    };

    for (auto &i : inputs)
    {
        std::stringstream s(i.first);
        EXPECT_EQ(count_increasing_windows(s), i.second) << " on input " << i.first;
    }
}