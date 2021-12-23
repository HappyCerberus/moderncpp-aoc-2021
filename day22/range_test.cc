#include "range.h"

#include <gtest/gtest.h>

TEST(Range, Parse) {
  std::stringstream s("on x=-22..26,y=-27..20,z=-29..19\noff x=-48..-32,y=26..41,z=-47..-37\n");
  CuboidInstruction r;
  s >> r;
  EXPECT_EQ(r, CuboidInstruction({-22, -27, -29}, {26, 20, 19}, true));
  s >> r;
  EXPECT_EQ(r, CuboidInstruction({-48, 26, -47}, {-32, 41, -37}, false));
}

TEST(Range, Count) {
  {
    std::cerr << "------------------------------------\n";
    std::stringstream s("on x=10..12,y=10..12,z=10..12\non x=11..13,y=11..13,z=11..13\n");
    EXPECT_EQ(apply_instructions(s, {}), 46);
  }
  {
    std::cerr << "------------------------------------\n";
    std::stringstream s("on x=10..12,y=10..12,z=10..12\non x=11..13,y=11..13,z=11..13\noff x=9..11,y=9..11,z=9..11\n");
    EXPECT_EQ(apply_instructions(s, {}), 38);
  }
  {
    std::cerr << "------------------------------------\n";
    std::stringstream s("on x=10..12,y=10..12,z=10..12\non x=11..13,y=11..13,z=11..13\noff x=9..11,y=9..11,z=9..11\non x=10..10,y=10..10,z=10..10\n");
    EXPECT_EQ(apply_instructions(s, {}), 39);
  }
}