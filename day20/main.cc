#include "filter.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <ranges>

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

  Image img, copy;
  input >> img;
  copy = img;

  img.enhance();
  img.enhance();
  std::cout << "After enhancing the input twice, " << img.lit_pixels() << " pixels are lit.\n";

  for (int i = 0; i < 50; i++)
    copy.enhance();
  std::cout << "After enhancing the image 50x " << copy.lit_pixels() << " pixels are lit.\n";
}