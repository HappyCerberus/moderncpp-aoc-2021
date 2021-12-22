#include "range.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>

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

  std::cout << "Sum = " << apply_instructions(input, {}) << "\n";
}