#include "polymer.h"

#include <gtest/gtest.h>


TEST(Polymer, FreqCounting) {

  std::stringstream input(
      "NNCB\n\nCH -> B\nHH -> N\nCB -> H\nNH -> C\nHB -> C\nHC -> B\nHN -> C\nNN -> C\nBH -> H\nNC -> B\nNB -> B\nBN -> B\nBB -> N\nBC -> B\nCC -> N\nCN -> C");
  auto [base, rules] = parse_rules(input);
  {
    FrequencyCounter counter(base);
    counter.tick(rules);
    EXPECT_EQ(counter.char_freq['B' - 'A'], 2);
    EXPECT_EQ(counter.char_freq['C' - 'A'], 2);
    EXPECT_EQ(counter.char_freq['H' - 'A'], 1);
    EXPECT_EQ(counter.char_freq['N' - 'A'], 2);

    EXPECT_EQ(counter.pair_freq[Pair('N', 'C')], 1);
    EXPECT_EQ(counter.pair_freq[Pair('C', 'N')], 1);
    EXPECT_EQ(counter.pair_freq[Pair('N', 'B')], 1);
    EXPECT_EQ(counter.pair_freq[Pair('B', 'C')], 1);
    EXPECT_EQ(counter.pair_freq[Pair('C', 'H')], 1);
    EXPECT_EQ(counter.pair_freq[Pair('H', 'B')], 1);
  }
  {
    FrequencyCounter counter(base);
    for (int i = 0; i < 10; i++) {
      counter.tick(rules);
    }
    EXPECT_EQ(counter.char_freq['B' - 'A'], 1749);
    EXPECT_EQ(counter.char_freq['C' - 'A'], 298);
  }
}