#include "diagonals.h"

#include <gtest/gtest.h>
#include <sstream>
#include <unordered_set>

TEST(DiagonalsTest, SinglePoint) {
  Line l1{{0, 0}, {4, 4}};
  Line l2{{0, 4}, {4, 0}};

  EXPECT_EQ(l1.xdir(), 1);
  EXPECT_EQ(l2.xdir(), 1);
  EXPECT_EQ(l1.ydir(), 1);
  EXPECT_EQ(l2.ydir(), -1);

  EXPECT_EQ(l1.single_point_intersect(l2), Point(2, 2));

  Line l3{{0, 0}, {5, 5}};
  Line l4{{0, 5}, {5, 0}};
  EXPECT_FALSE(l3.single_point_intersect(l4));

  Line bug1{{0, 9}, {5, 9}};
  Line bug2{{0, 8}, {8, 0}};
  EXPECT_FALSE(bug1.single_point_intersect(bug2));

  Line bug3{{0, 8}, {8, 0}};
  Line bug4{{7, 0}, {7, 4}};
  EXPECT_EQ(bug3.single_point_intersect(bug4), Point(7, 1));
}

TEST(DiagonalsTest, Overlay) {
  Line l1{{0, 0}, {10, 0}};
  EXPECT_TRUE(l1.does_overlay(l1));
  EXPECT_FALSE(l1.does_overlay(Line{{0, 1}, {10, 1}}));
  EXPECT_TRUE(l1.does_overlay(Line{{20, 0}, {21, 0}}));

  Line l2{{0, 0}, {5, 5}};
  EXPECT_TRUE(l2.does_overlay(l2));
  EXPECT_FALSE(l2.does_overlay(l1));
  EXPECT_TRUE(l2.does_overlay(Line{{1, 1}, {2, 2}}));
  EXPECT_FALSE(l2.does_overlay(Line{{2, 1}, {1, 2}}));
}

TEST(DiagonalsTest, Intersect) {
  Line l1{{0, 0}, {10, 10}};
  EXPECT_TRUE(l1.does_intersect(l1));
  EXPECT_EQ(l1.intersect(l1), l1);

  Line l2{{2, 2}, {4, 4}};
  EXPECT_TRUE(l1.does_intersect(l2));
  EXPECT_EQ(l1.intersect(l2), l2);

  Line l3{{0, 10}, {10, 0}};
  EXPECT_TRUE(l3.does_intersect(l3));
  EXPECT_EQ(l3.intersect(l3), l3);

  Line l4{{1, 9}, {9, 1}};
  EXPECT_TRUE(l3.does_intersect(l4));
  EXPECT_EQ(l3.intersect(l4), l4);

  EXPECT_FALSE(l3.does_intersect(Line{{2, 9}, {9, 2}}));
  EXPECT_EQ(l4.intersect(l3), l4);
  EXPECT_EQ(l4.intersect(Line{{2, 8}, {10, 0}}), Line({2, 8}, {9, 1}));
}