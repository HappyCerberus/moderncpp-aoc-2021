#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>
#include <ranges>
#include <vector>

#include "snail-number.h"

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

  std::vector<SnailNumber> numbers;
  std::ranges::copy(std::ranges::istream_view<SnailNumber>(input), std::back_inserter(numbers));
  SnailNumber sum = std::accumulate(numbers.begin() + 1, numbers.end(), numbers[0], std::plus<>());
  std::cout << "The magnitude of the final sum is " << static_cast<uint64_t>(sum) << "\n";

  uint64_t best = 0;
  for (size_t i = 0; i < numbers.size(); i++) {
    for (size_t j = i + 1; j < numbers.size(); j++) {
      best = std::max({best, static_cast<uint64_t>(numbers[i] + numbers[j]), static_cast<uint64_t>(numbers[j] + numbers[i])});
    }
  }
  std::cout << "Maximum reachable magnitude is " << best << "\n";
}