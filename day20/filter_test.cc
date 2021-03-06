#include "filter.h"

#include <gtest/gtest.h>

const char *INPUT =
    R"input(..#.#..#####.#.#.#.###.##.....###.##.#..###.####..#####..#....#..#..##..###..######.###...####..#..#####..##..#.#####...##.#.#..#.##..#.#......#.###.######.###.####...#.##.##..#..#..#####.....#.#....###..#.##......#.....#..#..#..##..#...##.######.####.####.#.#...#.......#..#.#.#...####.##.#......#..#...##.#.##..#...##.#.##..###.#......#.#.......#.#.#.####.###.##...#.....####.#..#..#.##.#....##..#.####....##...##..#...#......#.#.......#.......##..####..#...#.#.#...##..#.#..###..#####........#..####......#..#

#..#.
#....
##..#
..#..
..###)input";

#include <sstream>

TEST(Filter, FromAoC) {
  std::stringstream s(INPUT);
  Image img;
  s >> img;
  EXPECT_EQ(img.data.size(), 5);
  EXPECT_EQ(img.encoded_number(2, 2), 34);

  EXPECT_EQ(img.lit_pixels(), 10);
  img.enhance();
  img.enhance();
  EXPECT_EQ(img.lit_pixels(), 35);

  std::cerr << img << "\n\n";
}