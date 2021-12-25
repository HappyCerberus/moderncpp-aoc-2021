#include <fstream>
#include <iostream>

#include "seabed.h"

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

  SeaBed seabed = parse_seabed(input);

  size_t moves = 1;
  while (true) {
    auto [next, cnt] = tick(seabed);
    if (cnt == 0) {
      std::cout << "The cucumbers stopped moving after " << moves << " steps.\n";
      return 0;
    }
    moves++;
    seabed = std::move(next);
  }
}