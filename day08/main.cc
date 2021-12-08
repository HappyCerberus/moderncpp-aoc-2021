#include "parsing.h"
#include "wiring.h"

#include <algorithm>
#include <bit>
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

  std::string input_line;
  uint32_t part1_total = 0;
  uint32_t part2_total = 0;
  while (getline(input, input_line)) {
    Puzzle p = parse_line(input_line);
    part1_total += std::ranges::count_if(p.numbers, [](auto num) {
      uint8_t cnt = cnt_segments(num);
      return cnt == 2 || cnt == 3 || cnt == 4 || cnt == 7;
    });
    Wiring w = solve_wiring(p);
    part2_total += decode_number(p, w);
  }

  std::cout << "Total number of numbers with unique number of segments (1, 4, 7, 8) is " << part1_total << "\n";
  std::cout << "Sum of all decoded numbers is " << part2_total << "\n";
}