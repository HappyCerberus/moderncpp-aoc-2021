#include "search-with-memory.h"

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

  Graph graph = parse_graph(input);
  std::cout << "Total paths through the caves " << count_paths(graph) << "\n";
  std::cout << "Total paths through the caves that revisit small caves " << count_complex_paths(graph) << "\n";
}