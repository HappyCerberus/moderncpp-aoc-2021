#include "flood-fill.h"
#include "heightmap.h"

#include <gtest/gtest.h>
#include <sstream>

TEST(HeightmapTest, Simple) {
  std::stringstream s("2199943210\n3987894921\n9856789892\n8767896789\n9899965678\n");

  auto map = read_heightmap(s);
  EXPECT_EQ(flood_fill(map, 0, 0), 3);
  EXPECT_EQ(flood_fill(map, 0, 6), 9);
  EXPECT_EQ(flood_fill(map, 1, 2), 14);
  EXPECT_EQ(flood_fill(map, 2, 7), 9);
}