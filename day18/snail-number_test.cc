#include "snail-number.h"

#include <gtest/gtest.h>

TEST(SnailNumber, Literal) {
  std::unordered_map<std::string, uint64_t> test_data = {
      {"[[1,2],[[3,4],5]]", 143},
      {"[[[[0,7],4],[[7,8],[6,0]]],[8,1]]", 1384},
      {"[[[[1,1],[2,2]],[3,3]],[4,4]]", 445},
      {"[[[[3,0],[5,3]],[4,4]],[5,5]]", 791},
      {"[[[[5,0],[7,4]],[5,5]],[6,6]]", 1137},
      {"[[[[8,7],[7,7]],[[8,6],[7,7]]],[[[0,7],[6,6]],[8,7]]]", 3488},
  };
  for (auto &[in, out] : test_data) {
    std::stringstream input(in);
    SnailNumber num;
    input >> num;
    EXPECT_EQ(static_cast<uint64_t>(num), out);
  }
}

TEST(SnailNumber, Plus) {
  std::stringstream data("[1,2]");
  SnailNumber left;
  data >> left;
  data.str("[3,4]");
  SnailNumber right;
  data >> right;
  SnailNumber result = left + right;
  data.str("");
  data << result;
  EXPECT_EQ(data.str(), "[[1,2],[3,4]]");
}

bool one_explode(SnailNumber &num) { return num.explodes(); }

bool one_split(SnailNumber &num) { return num.splits(); }

TEST(SnailNumber, Explodes) {
  std::unordered_map<std::string, std::string> test_data = {
      {"[[[[[9,8],1],2],3],4]", "[[[[0,9],2],3],4]"},
      {"[7,[6,[5,[4,[3,2]]]]]", "[7,[6,[5,[7,0]]]]"},
      {"[[6,[5,[4,[3,2]]]],1]", "[[6,[5,[7,0]]],3]"},
      {"[[3,[2,[1,[7,3]]]],[6,[5,[4,[3,2]]]]]", "[[3,[2,[8,0]]],[9,[5,[4,[3,2]]]]]"},
      {"[[3,[2,[8,0]]],[9,[5,[4,[3,2]]]]]", "[[3,[2,[8,0]]],[9,[5,[7,0]]]]"},
  };
  for (auto &[in, out] : test_data) {
    std::stringstream data(in);
    SnailNumber num;
    data >> num;
    one_explode(num);
    data.str("");
    data << num;
    EXPECT_EQ(data.str(), out);
  }
}

TEST(SnailNumber, Splits) {
  std::stringstream data;
  data.str("[[[[4,3],4],4],[7,[[8,4],9]]]");
  SnailNumber left;
  data >> left;

  data.str("[1,1]");
  SnailNumber right;
  data >> right;

  SnailNumber result = left + right;
  data.str("");
  data << result;
  EXPECT_EQ(data.str(), "[[[[0,7],4],[[7,8],[6,0]]],[8,1]]");
}

TEST(SnailNumber, Homework) {
  std::stringstream data(
      "[[[0,[5,8]],[[1,7],[9,6]]],[[4,[1,2]],[[1,4],2]]]\n[[[5,[2,8]],4],[5,[[9,9],0]]]\n[6,[[[6,2],[5,6]],[[7,6],[4,7]]]]\n"
      "[[[6,[0,7]],[0,9]],[4,[9,[9,0]]]]\n[[[7,[6,4]],[3,[1,3]]],[[[5,5],1],9]]\n[[6,[[7,3],[3,2]]],[[[3,8],[5,7]],4]]\n"
      "[[[[5,4],[7,7]],8],[[8,3],8]]\n[[9,3],[[9,9],[6,[4,9]]]]\n[[2,[[7,7],7]],[[5,8],[[9,3],[0,2]]]]\n[[[[5,2],5],[8,[3,7]]],[[5,[7,5]],[4,4]]]\n");
  SnailNumber sum;
  data >> sum;
  SnailNumber tmp;
  while (data >> tmp) {
    sum = sum + tmp;
    std::cerr << sum << "\n";
  }
  data.str("");
  data.clear();
  data << sum;
  EXPECT_EQ(data.str(), "[[[[6,6],[7,6]],[[7,7],[7,0]]],[[[7,7],[7,7]],[[7,8],[9,9]]]]");
  EXPECT_EQ(static_cast<uint64_t>(sum), 4140);
}