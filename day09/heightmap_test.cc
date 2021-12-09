#include "heightmap.h"

#include <gtest/gtest.h>
#include <sstream>

TEST(HeightmapTest, Simple) {
  std::stringstream s("2199943210\n3987894921\n9856789892\n8767896789\n9899965678\n");

  auto map = read_heightmap(s);
  EXPECT_EQ(map.size(), 5);
  EXPECT_EQ(map[0].size(), 10);
  EXPECT_EQ(map[1][1], 9);

  EXPECT_TRUE(is_low_point(map, 0, 1));
  EXPECT_TRUE(is_low_point(map, 0, 9));
  EXPECT_TRUE(is_low_point(map, 2, 2));
  EXPECT_TRUE(is_low_point(map, 4, 6));
  EXPECT_FALSE(is_low_point(map, 3, 3));
}