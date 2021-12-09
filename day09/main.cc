#include "flood-fill.h"
#include "heightmap.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <queue>

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

  uint32_t result = 0;
  HeightMap map = read_heightmap(input);
  for (size_t row = 0; row < map.size(); row++) {
    for (size_t column = 0; column < map[row].size(); column++) {
      if (is_low_point(map, row, column))
        result += map[row][column] + 1;
    }
  }
  std::cout << "Total risk level of all low points is " << result << "\n";

  std::vector<uint32_t> sizes;
  for (uint32_t row = 0; row < map.size(); row++) {
    for (uint32_t column = 0; column < map[row].size(); column++) {
      uint32_t size = flood_fill(map, row, column);
      if (size != 0)
        sizes.push_back(size);
    }
  }
  std::cout << "Total of non-zero sized basins: " << sizes.size() << "\n";
  std::ranges::sort(sizes, std::greater<int>());
  std::cout << "Result of multiplying all basin sizes is " << sizes[0] * sizes[1] * sizes[2] << "\n";
}