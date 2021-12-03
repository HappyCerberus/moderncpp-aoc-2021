#include "ratings.h"

#include <gtest/gtest.h>

TEST(RatingsTest, Ratings) {
  std::vector<std::pair<std::vector<std::bitset<5>>, Ratings>> inputs = {
      {{0b11111, 0b00000}, {.oxygen_generator = 0b11111, .co2_scrubber = 0b00000}},
      {{0b11111, 0b10111, 0b10111, 0b00111, 0b01111}, {.oxygen_generator = 0b10111, .co2_scrubber = 0b00111}},
      {{0b11111, 0b11110, 0b01111, 0b01000}, {.oxygen_generator = 0b11111, .co2_scrubber = 0b01000}},
      {{0b00100, 0b11110, 0b10110, 0b10111, 0b10101, 0b01111, 0b00111, 0b11100, 0b10000, 0b11001, 0b00010, 0b01010},
       {.oxygen_generator = 0b10111, .co2_scrubber = 0b01010}},
  };

  for (auto &i : inputs) {
    std::cerr << "---------\n";
    EXPECT_EQ(find_rating<5>(i.first), i.second);
  }
}