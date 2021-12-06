#include "lanternfish.h"

#include <fstream>
#include <iostream>
#include <string>

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

  std::string starting_pop;
  if (!getline(input, starting_pop))
    throw std::runtime_error("Failed to read input.");

  constexpr const uint32_t days_part1 = 80;
  {
    Population pop;
    init_population(pop, starting_pop);
    for (uint32_t i = 0; i < days_part1; i++)
      simulate_day(pop);
    std::cout << "Simulated population size of lanternfish after " << days_part1 << " is " << total_pop_count(pop) << "\n";
  }

  constexpr const uint32_t days_part2 = 256;
  {
    Population pop;
    init_population(pop, starting_pop);
    for (uint32_t i = 0; i < days_part2; i++)
      simulate_day(pop);
    std::cout << "Simulated population size of lanternfish after " << days_part2 << " is " << total_pop_count(pop) << "\n";
  }
  return 0;
}