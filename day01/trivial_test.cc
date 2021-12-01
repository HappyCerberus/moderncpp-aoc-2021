#include "trivial.h"

#include <gtest/gtest.h>
#include <sstream>

TEST(TrivialTest, Simple)
{
    std::vector<std::pair<std::string, uint32_t>> inputs = {
        {"", 0},                // empty input 0 increasing
        {"0", 0},               // single element 0 increasing
        {"0 1", 1},             // two elements, with increase
        {"0 1 0 1 0 1 0 1", 4}, // alternating, 4 repetitions
        {"0 0 0 0 0 0", 0},     // monotonic, no increase
        {"0 1 2 3", 3},         // increasing sequence - 3 increases
        {"3 2 1 0", 0},         // decreasing sequence - 0 increases
    };

    for (auto &i : inputs)
    {
        std::stringstream s(i.first);
        EXPECT_EQ(count_increasing(s), i.second) << " on input " << i.first;
    }
}