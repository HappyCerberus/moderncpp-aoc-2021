#include "point.h"
#include "scanner.h"

#include <algorithm>
#include <deque>
#include <fstream>
#include <iostream>
#include <iterator>
#include <ranges>
#include <unordered_set>

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

  std::vector<Scanner> scanners;
  std::ranges::copy(std::ranges::istream_view<Scanner>(input), std::back_insert_iterator(scanners));
  if (scanners.size() != 26)
    throw std::runtime_error("Failed to read input.");
  normalize_scanners(scanners, 12);

  std::unordered_set<Beacon> unique_beacons;
  for (const auto &s : scanners)
    for (const auto &b : s.beacons)
      unique_beacons.insert(b);
  std::cout << "Detected " << unique_beacons.size() << " unique beacons.\n";

  int64_t best = 0;
  for (auto lhs : scanners)
    for (auto rhs : scanners)
      best = std::max(best, (lhs.position - rhs.position).manhattan());
  std::cout << "Biggest Manhattan distance between two scanners is " << best << "\n";
}