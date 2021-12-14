#include "lazy-brute-force.h"

#include <gtest/gtest.h>

TEST(LazyBruteForce, BaseGeneratorTest) {
  std::string target = "abcdefgh";
  std::string result;
  for (auto c : polymer_expander(target)) {
    result += c;
  }
  EXPECT_EQ(result, target);
}

TEST(LazyBruteForce, GeneratorWithRules) {
  std::string target = "ababa";
  std::string src = "aaa";
  std::string result;
  InsertionRules rules = {{{'a', 'a'}, {'b'}}};
  for (auto c : polymer_expander(rules, polymer_expander(src))) {
    result += c;
  }
  EXPECT_EQ(result, target);
}

TEST(LazyBruteForce, FromAoC) {
  std::stringstream input(
      "NNCB\n\nCH -> B\nHH -> N\nCB -> H\nNH -> C\nHB -> C\nHC -> B\nHN -> C\nNN -> C\nBH -> H\nNC -> B\nNB -> B\nBN -> B\nBB -> N\nBC -> B\nCC -> N\nCN -> C");
  auto [base, rules] = parse_rules(input);

  std::string result;
  {
    auto expander = polymer_expander(base);
    for (int i = 0; i < 1; i++)
      expander = polymer_expander(rules, std::move(expander));
    for (auto c : expander) {
      result += c;
    }
  }
  EXPECT_EQ(result, "NCNBCHB");

  result = "";
  {
    auto expander = polymer_expander(base);
    for (int i = 0; i < 2; i++)
      expander = polymer_expander(rules, std::move(expander));
    for (auto c : expander) {
      result += c;
    }
  }
  EXPECT_EQ(result, "NBCCNBBBCBHCB");

  result = "";
  {
    auto expander = polymer_expander(base);
    for (int i = 0; i < 3; i++)
      expander = polymer_expander(rules, std::move(expander));
    for (auto c : expander) {
      result += c;
    }
  }
  EXPECT_EQ(result, "NBBBCNCCNBBNBNBBCHBHHBCHB");

  result = "";
  {
    auto expander = polymer_expander(base);
    for (int i = 0; i < 4; i++)
      expander = polymer_expander(rules, std::move(expander));
    for (auto c : expander) {
      result += c;
    }
  }
  EXPECT_EQ(result, "NBBNBNBBCCNBCNCCNBBNBBNBBBNBBNBBCBHCBHHNHCBBCBHCB");
}