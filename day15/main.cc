#include "cave.h"

#include <chrono>
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

  Cave cave = parse_cave(input);
  std::cout << "The cheapest found path will cost " << least_path_cost(cave) << "\n";
  Cave big_cave = expand_cave(cave);
  auto start = std::chrono::steady_clock::now();
  std::cout << "The cheapest found path in the full cave will cost " << least_path_cost(big_cave) << "\n";
  auto mid = std::chrono::steady_clock::now();
  std::cout << "The cheapest found path in the full cave will cost " << least_path_cost_fast(big_cave) << "\n";
  auto done = std::chrono::steady_clock::now();
  std::cout << "Slow version took " << (mid - start) << ".\n";
  std::cout << "Fast version took " << (done - mid) << ".\n";
}