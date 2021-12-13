#include "fold.h"

#include <gtest/gtest.h>

TEST(Fold, SingleDimension) {
  EXPECT_EQ(fold_number(10, 5), 0);
  EXPECT_EQ(fold_number(8, 6), 4);
}

TEST(Fold, Parsing) {
  std::stringstream input(
      "6,10\n0,14\n9,10\n0,3\n10,4\n4,11\n6,0\n6,12\n4,1\n0,13\n10,12\n3,4\n3,0\n8,4\n1,10\n2,14\n8,10\n9,0\n\nfold along y=7\nfold along x=5\n");
  Paper in = parse_input(input);

  EXPECT_TRUE(in.points.contains({6, 10}));
  EXPECT_TRUE(in.points.contains({9, 0}));
  EXPECT_TRUE(in.points.contains({4, 1}));
  EXPECT_EQ(in.folds.size(), 2);
  EXPECT_EQ(in.folds[0].direction, Fold::Y_FOLD);
  EXPECT_EQ(in.folds[0].number, 7);
  EXPECT_EQ(in.folds[1].direction, Fold::X_FOLD);
  EXPECT_EQ(in.folds[1].number, 5);
}

TEST(Fold, SingleFold) {
  std::stringstream input(
      "6,10\n0,14\n9,10\n0,3\n10,4\n4,11\n6,0\n6,12\n4,1\n0,13\n10,12\n3,4\n3,0\n8,4\n1,10\n2,14\n8,10\n9,0\n\nfold along y=7\nfold along x=5\n");
  Paper in = parse_input(input);
  first_fold(in);

  EXPECT_EQ(in.points.size(), 17);
  EXPECT_TRUE(in.points.contains({4, 1}));
  EXPECT_TRUE(in.points.contains({6, 4}));
}