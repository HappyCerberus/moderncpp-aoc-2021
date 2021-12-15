#include "cave.h"

#include <gtest/gtest.h>

TEST(Cave, SimpleSearch) {
  std::stringstream input("1163751742\n1381373672\n2136511328\n3694931569\n7463417111\n1319128137\n1359912421\n3125421639\n1293138521\n2311944581\n");
  Cave cave = parse_cave(input);
  EXPECT_EQ(least_path_cost(cave), 40);
}

TEST(Cave, ExpandedSearch) {
  std::stringstream input("1163751742\n1381373672\n2136511328\n3694931569\n7463417111\n1319128137\n1359912421\n3125421639\n1293138521\n2311944581\n");
  Cave cave = parse_cave(input);
  Cave big_cave = expand_cave(cave);
  EXPECT_EQ(least_path_cost(big_cave), 315);
}