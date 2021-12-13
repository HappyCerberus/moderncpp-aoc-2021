#include "fold.h"

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

  Paper paper = parse_input(input);
  {
    auto copy = paper;
    first_fold(copy);
    std::cout << "After first fold of paper " << copy.points.size() << " dots are visible.\n";
  }
  fold_paper(paper);
  std::cout << "Decoded:\n" << paper;
}