#include "lanternfish.h"

#include <gtest/gtest.h>

TEST(LanternfishTest, SimplePopulation) {
  Population pop;
  init_population(pop, "1,1,1,1");
  EXPECT_EQ(total_pop_count(pop), 4) << "Initial population.";
  simulate_day(pop);
  EXPECT_EQ(total_pop_count(pop), 4) << "Population after 1 day, should be ready to reproduce next day.";
  simulate_day(pop);
  EXPECT_EQ(total_pop_count(pop), 8) << "Should have reproduced.";
}

TEST(LaternfishTest, FromAoC1) {
  Population pop;
  init_population(pop, "3,4,3,1,2");
  for (int i = 0; i < 18; i++) {
    simulate_day(pop);
  }
  EXPECT_EQ(total_pop_count(pop), 26);
  for (int i = 0; i < 80 - 18; i++)
    simulate_day(pop);
  EXPECT_EQ(total_pop_count(pop), 5934);
}

TEST(LanternfishTest, FromAoc2) {
  Population pop;
  init_population(pop, "3,4,3,1,2");
  for (int i = 0; i < 256; i++)
    simulate_day(pop);
  EXPECT_EQ(total_pop_count(pop), UINT64_C(26984457539));
}