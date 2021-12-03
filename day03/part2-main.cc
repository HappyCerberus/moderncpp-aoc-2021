#include <algorithm>
#include <bitset>
#include <fstream>
#include <iostream>
#include <ranges>

#include "ratings.h"

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

  std::vector<std::bitset<12>> data;
  std::ranges::copy(std::ranges::istream_view<std::bitset<12>>(input), std::back_inserter(data));

  auto ratings = find_rating<12>(data);
  std::cout << "Found ratings : [oxygen generator=" << ratings.oxygen_generator << ", co2 scrubber=" << ratings.co2_scrubber << "]\n";
  std::cout << "Output =  " << ratings.oxygen_generator * ratings.co2_scrubber << "\n";

  return 0;
}