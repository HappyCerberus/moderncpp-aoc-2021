#include "parsing.h"

#include <gtest/gtest.h>
#include <sstream>

TEST(ParsingTest, Simple) {
  Puzzle puzzle = parse_line("acedgfb cdfbe gcdfa fbcad dab cefabd cdfgeb eafb cagedb ab | cdfeb fcadb cdfeb cdbaf");
  EXPECT_EQ(puzzle.patterns.size(), 10);
  EXPECT_EQ(puzzle.numbers.size(), 4);
  EXPECT_EQ(puzzle.patterns[4], 1 + 2 + 8);
  EXPECT_EQ(puzzle.patterns[9], 1 + 2);
}