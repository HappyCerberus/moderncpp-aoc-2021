#include "flashing.h"

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

  Cavern cave = parse_cavern(input);
  uint32_t total = 0;
  for (int i = 1;; i++) {
    uint32_t flash_cnt = tick(cave);
    total += flash_cnt;
    if (i == 100)
      std::cout << "Total number of flashes upto tick 100: " << total << "\n";
    if (flash_cnt == cave.size() * cave.size()) {
      std::cout << "Synchronized at tick " << i << "\n";
      if (i > 100)
        break;
    }
  }
}