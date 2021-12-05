#include "lines.h"

#include <gtest/gtest.h>

TEST(LinesTest, Intersection) {
  Line l1{{0, 0}, {10, 0}};
  Line l2{{2, 0}, {4, 0}};

  EXPECT_TRUE(l1.does_intersect(l1));
  EXPECT_EQ(l1.intersect(l1), l1);

  EXPECT_TRUE(l1.does_intersect(l2));
  EXPECT_EQ(l1.intersect(l2), l2);

  Line l3{{5, 0}, {12, 0}};

  EXPECT_TRUE(l1.does_intersect(l3));
  EXPECT_EQ(l1.intersect(l3), Line({5, 0}, {10, 0}));

  Line l5{{5, 1}, {10, 1}};

  EXPECT_FALSE(l1.does_intersect(l5));
  EXPECT_FALSE(l1.intersect(l5)); // empty optional

  Line l6{{6, 0}, {6, 20}};

  EXPECT_TRUE(l1.does_intersect(l6));
  EXPECT_EQ(l1.intersect(l6), Line({6, 0}, {6, 0}));

  Line l7{{1, 2}, {1, 2}};
  EXPECT_TRUE(l7.does_intersect(l7));
  EXPECT_EQ(l7.intersect(l7), l7);
}