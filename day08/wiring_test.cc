#include "parsing.h"
#include "wiring.h"

#include <gtest/gtest.h>
#include <sstream>

TEST(WiringTest, FromAoC) {
  Puzzle p = parse_line("acedgfb cdfbe gcdfa fbcad dab cefabd cdfgeb eafb cagedb ab | cdfeb fcadb cdfeb cdbaf");
  Wiring w = solve_wiring(p);
  EXPECT_EQ(w[0], SEGMENT_C); // A -> C
  EXPECT_EQ(w[1], SEGMENT_F); // B -> F
  EXPECT_EQ(w[2], SEGMENT_G); // C -> G
  EXPECT_EQ(w[3], SEGMENT_A); // D -> A
  EXPECT_EQ(w[4], SEGMENT_B); // E -> B
  EXPECT_EQ(w[5], SEGMENT_D); // F -> D
  EXPECT_EQ(w[6], SEGMENT_E); // G -> E

  EXPECT_EQ(decode_number(p, w), 5353);
}