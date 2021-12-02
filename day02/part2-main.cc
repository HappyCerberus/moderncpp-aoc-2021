#include <fstream>
#include <iostream>

#include "with-aim.h"

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

  auto position = navigate(input);
  std::cout << "We navigated to " << position.depth << " - " << position.distance << ".\n";
  std::cout << "Position rectangle = " << position.depth * position.distance << "\n";

  return 0;
}