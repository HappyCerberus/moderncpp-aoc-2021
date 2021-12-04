#include "bingo.h"

#include <gtest/gtest.h>
#include <sstream>
#include <string>

TEST(BingoTest, OneBoard) {
  State state;
  std::string input = "1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25";
  std::stringstream s(input);
  s >> state;
  EXPECT_TRUE(s.eof());

  std::string draws = "1, 2, 3, 4, 5";
  EXPECT_EQ(process_draws(state, draws), 1550) << "310 (first board unmarked sum) * 5 (drawn number) = 1550";
}

TEST(BingoTest, FromAoC) {
  State state;
  std::string input = "22 13 17 11  0  8  2 23  4 24 21  9 14 16  7  6 10  3 18  5  1 12 20 15 19 "
                      " 3 15  0  2 22  9 18 13 17  5 19  8  7 25 23 20 11 10 24  4 14 21 16 12  6 "
                      "14 21 17 24  4 10 16 15  9 19 18  8 23 26 20 22 11 13  6  5  2  0 12  3  7";
  std::stringstream s(input);
  s >> state;
  EXPECT_TRUE(s.eof());

  std::string draws = "7, 4, 9, 5, 11, 17, 23, 2, 0, 14, 21, 24, 10, 16, 13, 6, 15, 25, 12, 22, 18, 20, 8, 19, 3, 26, 1";
  EXPECT_EQ(process_draws(state, draws), 4512);
}

TEST(BingoTest, LastOneBoard) {
  State state;
  std::string input = "1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25";
  std::stringstream s(input);
  s >> state;
  EXPECT_TRUE(s.eof());

  std::string draws = "1, 2, 3, 4, 5";
  EXPECT_EQ(process_draws_until_last(state, draws), 1550) << "310 (first board unmarked sum) * 5 (drawn number) = 1550";
}

TEST(BingoTest, LastOneFromAoC) {
  State state;
  std::string input = "22 13 17 11  0  8  2 23  4 24 21  9 14 16  7  6 10  3 18  5  1 12 20 15 19 "
                      " 3 15  0  2 22  9 18 13 17  5 19  8  7 25 23 20 11 10 24  4 14 21 16 12  6 "
                      "14 21 17 24  4 10 16 15  9 19 18  8 23 26 20 22 11 13  6  5  2  0 12  3  7";
  std::stringstream s(input);
  s >> state;
  EXPECT_TRUE(s.eof());

  std::string draws = "7, 4, 9, 5, 11, 17, 23, 2, 0, 14, 21, 24, 10, 16, 13, 6, 15, 25, 12, 22, 18, 20, 8, 19, 3, 26, 1";
  EXPECT_EQ(process_draws_until_last(state, draws), 1924);
}