#include "room.h"

#include <gtest/gtest.h>

TEST(Room, Constr) {
  Room a{'A', {'.', '.'}};
  EXPECT_FALSE(a.has_visitors());
  EXPECT_FALSE(a.is_finished());
  EXPECT_TRUE(a.can_accept());
}

TEST(Room, Simple) {
  Room a{'C', {'C', 'C', 'B', 'A'}};
  EXPECT_TRUE(a.has_visitors());
  EXPECT_FALSE(a.is_finished());
  EXPECT_FALSE(a.can_accept());
  EXPECT_EQ(a.top(), 'A');
  EXPECT_EQ(a.pop(), 1);

  EXPECT_EQ(a.top(), 'B');
  EXPECT_FALSE(a.is_finished());
  EXPECT_FALSE(a.can_accept());
  EXPECT_TRUE(a.has_visitors());
  EXPECT_EQ(a.pop(), 20);

  EXPECT_EQ(a.top(), 'C');
  EXPECT_FALSE(a.is_finished());
  EXPECT_TRUE(a.can_accept());
  EXPECT_FALSE(a.has_visitors());

  EXPECT_EQ(a.push('C'), 200);
  EXPECT_EQ(a.push('C'), 100);
  EXPECT_TRUE(a.is_finished());
  EXPECT_FALSE(a.can_accept());
  EXPECT_FALSE(a.has_visitors());
}
