#include "crabs.h"

#include <gtest/gtest.h>
#include <sstream>

TEST(CrabSubmarinesTest, Simple) {
  std::stringstream input("0,2,2,3");
  CrabSubmarines crabs = parse_input(input);
  EXPECT_EQ(minimum_fuel_to_aling(crabs), 3);
}

TEST(CrabSubmarinesTest, FromAoC) {
  std::stringstream input("16,1,2,0,4,2,7,1,2,14");
  CrabSubmarines crabs = parse_input(input);
  EXPECT_EQ(minimum_fuel_to_aling(crabs), 37);
}

TEST(CrabSubmarinesTest, FromAoCPart1v2) {
  std::stringstream input("16,1,2,0,4,2,7,1,2,14");
  CrabSubmarines crabs = parse_input(input);
  EXPECT_EQ(minimum_fuel_to_properly_align(crabs, [](int32_t target, int32_t el) { return std::abs(target - el); }), 37);
}

TEST(CrabSubmarinesTest, FromAoCPart2) {
  std::stringstream input("16,1,2,0,4,2,7,1,2,14");
  CrabSubmarines crabs = parse_input(input);
  EXPECT_EQ(minimum_fuel_to_properly_align(crabs, [](int32_t target, int32_t el) { return std::abs(target - el) * (std::abs(target - el) + 1) / 2; }), 168);
}

TEST(CrabSubmarinesTest, FromAoCv3) {
  std::stringstream input("16,1,2,0,4,2,7,1,2,14");
  CrabSubmarines crabs = parse_input(input);
  EXPECT_EQ(minimum_fuel_to_aling_v3(crabs), 37);
}

TEST(CrabSubmarinesTest, FromAoCv4) {
  std::stringstream input("16,1,2,0,4,2,7,1,2,14");
  CrabSubmarines crabs = parse_input(input);
  EXPECT_EQ(minimum_fuel_to_aling_v4(crabs), 37);
}