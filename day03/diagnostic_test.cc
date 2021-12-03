#include "diagnostic.h"

#include <gtest/gtest.h>
#include <sstream>

TEST(DiagnosticTest, EpsilonRate) {
  std::vector<std::pair<std::pair<uint32_t, uint8_t>, uint32_t>> inputs = {{{0b01, 2}, 0b10}, {{0b001, 3}, 0b110}, {{0b11001100, 6}, 0b00110011}};
  for (auto &i : inputs) {
    EXPECT_EQ(epsilon_rate(i.first.first, i.first.second), i.second);
  }
}

TEST(DiagnosticTest, GammaRateVector) {
  std::vector<std::pair<std::pair<std::vector<uint32_t>, uint8_t>, uint32_t>> inputs = {
      {{{0b1111, 0b0000}, 4}, 0b1111},
      {{{0b1111, 0b0000, 0b0000}, 4}, 0b0000},
      {{{0b1111, 0b1111, 0b0000}, 4}, 0b1111},
      {{{0b00100, 0b11110, 0b10110, 0b10111, 0b10101, 0b01111, 0b00111, 0b11100, 0b10000, 0b11001, 0b00010, 0b01010}, 5}, 0b10110},
  };

  for (auto &i : inputs) {
    EXPECT_EQ(gamma_rate(i.first.first, i.first.second), i.second);
  }
}

TEST(DiagnosticTest, GammaRateStream) {
  std::vector<std::pair<std::string, uint32_t>> inputs = {{"11111\n00000", 0b11111},
                                                          {"11111\n11111\n00000", 0b11111},
                                                          {"11111\n00000\n00000", 0b00000},
                                                          {"00100\n11110\n10110\n10111\n10101\n01111\n00111\n11100\n10000\n11001\n00010\n01010", 0b10110}};

  for (auto &i : inputs) {
    std::stringstream s(i.first);
    EXPECT_EQ(gamma_rate<5>(s), i.second) << "with input " << i.first;
  }
}