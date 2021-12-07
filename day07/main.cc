#include "crabs.h"

#include <fstream>
#include <iostream>

int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cerr << "This program expects one parameter that is the input file to read.\n";
    return 1;
  }
  std::ifstream input(argv[1]);
  if (!input.is_open()) {
    std::cerr << "Failed to open file.\n";
    return 1;
  }

  CrabSubmarines crabs = parse_input(input);
  {
    uint32_t fuel = minimum_fuel_to_aling_v4(crabs);
    std::cout << "Minimum fuel to align all crab submarines " << fuel << "\n";
  }
  {
    uint32_t fuel = minimum_fuel_to_properly_align(crabs, [](int32_t target, int32_t el) { return std::abs(target - el) * (std::abs(target - el) + 1) / 2; });
    std::cout << "Minimum fuel to properly align all crab submarines " << fuel << "\n";
  }

  return 0;
}