#include "brackets.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
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

  std::string line;
  std::unordered_map<char, uint32_t> points_check = {{')', 3}, {']', 57}, {'}', 1197}, {'>', 25137}};
  std::vector<uint64_t> fix_scores;
  uint32_t total_check = 0;
  uint32_t lines = 0;
  while (getline(input, line)) {
    if (char c = first_unmatched(line); c != '\0')
      total_check += points_check[c];
    else if (uint64_t score = autofix_score(autofix(line)); score != 0)
      fix_scores.push_back(score);

    lines++;
  }
  std::ranges::nth_element(fix_scores, begin(fix_scores) + fix_scores.size() / 2);
  std::cout << "Total error score on " << lines << " lines is " << total_check << "\n";
  std::cout << "Autofix middle score out of " << fix_scores.size() << " fixed lines is " << fix_scores[fix_scores.size() / 2] << "\n";
}