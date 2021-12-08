#include "display.h"

#include <gtest/gtest.h>
#include <sstream>

TEST(PuzzleTest, SegementCount) {
  EXPECT_EQ(cnt_segments(NUMBERS[0]), 6);
  EXPECT_EQ(cnt_segments(NUMBERS[1]), 2);
  EXPECT_EQ(cnt_segments(NUMBERS[2]), 5);
  EXPECT_EQ(cnt_segments(NUMBERS[3]), 5);
  EXPECT_EQ(cnt_segments(NUMBERS[4]), 4);
  EXPECT_EQ(cnt_segments(NUMBERS[5]), 5);
  EXPECT_EQ(cnt_segments(NUMBERS[6]), 6);
  EXPECT_EQ(cnt_segments(NUMBERS[7]), 3);
  EXPECT_EQ(cnt_segments(NUMBERS[8]), 7);
  EXPECT_EQ(cnt_segments(NUMBERS[9]), 6);
}