#include "flashing.h"

#include <gtest/gtest.h>

TEST(CavernTest, FromAoCSimple) {
  std::stringstream input("5483143223\n2745854711\n5264556173\n6141336146\n6357385478\n4167524645\n2176841721\n6882881134\n4846848554\n5283751526\n");
  Cavern cave = parse_cavern(input);
  EXPECT_EQ(cave.size(), 10);
  EXPECT_EQ(cave[0].size(), 10);
  EXPECT_EQ(cave[1][1], 7);

  EXPECT_EQ(tick(cave), 0);
  EXPECT_EQ(tick(cave), 35);
  std::stringstream input2("8807476555\n5089087054\n8597889608\n8485769600\n8700908800\n6600088989\n6800005943\n0000007456\n9000000876\n8700006848\n");
  Cavern result = parse_cavern(input2);
  for (size_t r = 0; r < result.size(); r++) {
    for (size_t c = 0; c < result.size(); c++) {
      EXPECT_EQ(cave[r][c], result[r][c]) << "Pos: " << r << ", " << c;
    }
  }
}

TEST(CavernTest, FullTicks) {
  std::stringstream input("5483143223\n2745854711\n5264556173\n6141336146\n6357385478\n4167524645\n2176841721\n6882881134\n4846848554\n5283751526\n");
  Cavern cave = parse_cavern(input);
  uint32_t total = 0;
  int i = 0;
  for (; i < 10; i++) {
    total += tick(cave);
  }
  EXPECT_EQ(total, 204);
  for (; i < 100; i++) {
    total += tick(cave);
  }
  EXPECT_EQ(total, 1656);
}
