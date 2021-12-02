#include "with-aim.h"

#include <gtest/gtest.h>
#include <sstream>

TEST(NavigationTest, SingleLine) {
  std::vector<std::pair<std::string, Position>> inputs = {
      {"forward 10", {.depth = 0, .distance = 10, .aim = 0}},
      {"down 10", {.depth = 0, .distance = 0, .aim = 10}},
      {"up 10", {.depth = 0, .distance = 0, .aim = -10}},
  };

  for (auto &i : inputs) {
    Position pos{};
    navigate(pos, i.first);
    EXPECT_EQ(pos, i.second) << "with input " << i.first;
  }
}

TEST(NavigationTest, FullInput) {
  std::vector<std::pair<std::string, Position>> inputs = {
      {"forward 10\ndown 5\nup 2\nforward 2\n", {.depth = 6, .distance = 12, .aim = 3}},
      {"down 20\ndown 20\nup 40\nxxx 2\nforward 0\n", {.depth = 0, .distance = 0, .aim = 0}},
      {"down 20\ndown 20\nxxx 2\nforward 2\n", {.depth = 80, .distance = 2, .aim = 40}},
  };
  for (auto &i : inputs) {
    std::stringstream s(i.first);
    EXPECT_EQ(navigate(s), i.second) << "with input " << i.first;
  }
}