#include <algorithm>
#include <array>
#include <iostream>
#include <limits>
#include <memory>
#include <ranges>
#include <vector>

#include "puzzle.h"

int main() {
  Puzzle part1{.hallway = {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
               .rooms = {{'A', {'C', 'D'}}, {'B', {'A', 'A'}}, {'C', {'B', 'D'}}, {'D', {'B', 'C'}}}};
  std::cout << "Shortest solution cost for part1 " << find_shortest(part1).value() << "\n";

  Puzzle part2{.hallway = {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
               .rooms = {{'A', {'C', 'D', 'D', 'D'}}, {'B', {'A', 'B', 'C', 'A'}}, {'C', {'B', 'A', 'B', 'D'}}, {'D', {'B', 'C', 'A', 'C'}}}};
  std::cout << "Shortest solution cost for part2 " << find_shortest(part2).value() << "\n";
}