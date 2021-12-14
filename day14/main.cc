#include "lazy-brute-force.h"
#include "polymer.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <ranges>
#include <string>
#include <vector>

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

  auto [base, rules] = parse_rules(input);
  auto expander = polymer_expander(base);
  for (int i = 0; i < 10; i++) {
    expander = polymer_expander(rules, std::move(expander));
  }
  std::vector<uint32_t> freq(26, 0);
  for (char c : expander) {
    freq[c - 'A']++;
  }

  {
    auto non_zero = freq | std::ranges::views::filter([](auto v) { return v != 0; });
    auto [min, max] = std::ranges::minmax_element(non_zero);
    std::cout << "10 gen: " << *max - *min << "\n";
  }
  {
    FrequencyCounter counter(base);
    for (int i = 0; i < 40; i++) {
      counter.tick(rules);
    }
    auto non_zero = counter.char_freq | std::ranges::views::filter([](auto v) { return v != 0; });
    auto [min, max] = std::ranges::minmax_element(non_zero);
    std::cout << "40 gen: " << *max - *min << "\n";
  }
}