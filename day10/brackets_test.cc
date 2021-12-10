#include "brackets.h"

#include <gtest/gtest.h>

TEST(HeightmapTest, Simple) {
  EXPECT_EQ(first_unmatched("()"), '\0');
  EXPECT_EQ(first_unmatched("[]"), '\0');
  EXPECT_EQ(first_unmatched("([])"), '\0');
  EXPECT_EQ(first_unmatched("{()()()}"), '\0');
  EXPECT_EQ(first_unmatched("<([{}])>"), '\0');
  EXPECT_EQ(first_unmatched("[<>({}){}[([])<>]]"), '\0');
  EXPECT_EQ(first_unmatched("(((((((((())))))))))"), '\0');
  EXPECT_EQ(first_unmatched("(]"), ']');
  EXPECT_EQ(first_unmatched("{()()()>"), '>');
  EXPECT_EQ(first_unmatched("(((()))}"), '}');
  EXPECT_EQ(first_unmatched("<([]){()}[{}])"), ')');
}

TEST(BracketsTest, FromAoC) {
  EXPECT_EQ(first_unmatched("[({(<(())[]>[[{[]{<()<>>"), '\0');
  EXPECT_EQ(first_unmatched("[(()[<>])]({[<{<<[]>>("), '\0');
  EXPECT_EQ(first_unmatched("{([(<{}[<>[]}>{[]{[(<()>"), '}');
  EXPECT_EQ(first_unmatched("(((({<>}<{<{<>}{[]{[]{}"), '\0');
  EXPECT_EQ(first_unmatched("[[<[([]))<([[{}[[()]]]"), ')');
  EXPECT_EQ(first_unmatched("[{[{({}]{}}([{[{{{}}([]"), ']');
  EXPECT_EQ(first_unmatched("{<[[]]>}<{[{[{[]{()[[[]"), '\0');
  EXPECT_EQ(first_unmatched("[<(<(<(<{}))><([]([]()"), ')');
  EXPECT_EQ(first_unmatched("<{([([[(<>()){}]>(<<{{"), '>');
  EXPECT_EQ(first_unmatched("<{([{{}}[<[[[<>{}]]]>[]]"), '\0');
}

TEST(BracketsTest, FromAoC2) {
  EXPECT_EQ(autofix("[({(<(())[]>[[{[]{<()<>>"), "}}]])})]");
  EXPECT_EQ(autofix("[(()[<>])]({[<{<<[]>>("), ")}>]})");
  EXPECT_EQ(autofix("(((({<>}<{<{<>}{[]{[]{}"), "}}>}>))))");
  EXPECT_EQ(autofix("{<[[]]>}<{[{[{[]{()[[[]"), "]]}}]}]}>");
  EXPECT_EQ(autofix("<{([{{}}[<[[[<>{}]]]>[]]"), "])}>");

  EXPECT_EQ(autofix_score(autofix("[({(<(())[]>[[{[]{<()<>>")), 288957);
  EXPECT_EQ(autofix_score(autofix("[(()[<>])]({[<{<<[]>>(")), 5566);
  EXPECT_EQ(autofix_score(autofix("(((({<>}<{<{<>}{[]{[]{}")), 1480781);
  EXPECT_EQ(autofix_score(autofix("{<[[]]>}<{[{[{[]{()[[[]")), 995444);
  EXPECT_EQ(autofix_score(autofix("<{([{{}}[<[[[<>{}]]]>[]]")), 294);
}