#include <fstream>
#include <iostream>

#include "bingo.h"

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

  std::string draws;
  if (!std::getline(input, draws))
    throw std::runtime_error("Failed to read draws.");

  State state;
  input >> state;
  auto result = process_draws_until_last(state, draws);
  std::cout << "Output =  " << result << "\n";

  return 0;
}