#include <algorithm>
#include <bitset>
#include <fstream>
#include <iostream>

#include "diagnostic.h"

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

  std::vector<uint32_t> data;
  std::ranges::transform(std::ranges::istream_view<std::bitset<12>>(input), std::back_inserter(data), std::identity{}, &std::bitset<12>::to_ulong);

  uint32_t gamma = gamma_rate(data, 12);
  uint32_t epsilon = epsilon_rate(gamma, 12);
  std::cout << "Diagnostic output : [gama=" << gamma << ", epsilon=" << epsilon << "]\n";
  std::cout << "Output =  " << gamma * epsilon << "\n";

  return 0;
}