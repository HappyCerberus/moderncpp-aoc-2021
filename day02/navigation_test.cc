#include "navigation.h"

#include <gtest/gtest.h>
#include <sstream>

TEST(NavigationTest, SingleLine) {
  std::vector<std::pair<std::string, Position>> inputs = {
      {"forward 10", {.depth = 0, .distance = 10}},
      {"down 10", {.depth = 10, .distance = 0}},
      {"up 10", {.depth = -10, .distance = 0}},
  };

  for (auto &i : inputs) {
    EXPECT_EQ(navigate(i.first), i.second) << "with input " << i.first;
  }
}

TEST(NavigationTest, FullInput) {
  std::vector<std::pair<std::string, Position>> inputs = {{"forward 10\ndown 5\nup 2\nforward 2\n", {.depth = 3, .distance = 12}},
                                                          {"down 20\ndown 20\nup 40\nxxx 2\nforward 0\n", {.depth = 0, .distance = 0}}};
  for (auto &i : inputs) {
    std::stringstream s(i.first);
    EXPECT_EQ(navigate(s), i.second) << "with input " << i.first;
  }
}