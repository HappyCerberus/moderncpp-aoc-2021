#include <fstream>
#include <iostream>
#include <unordered_set>
#include <vector>

#include "lines.h"

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

  Line l;
  std::vector<Line> lines;
  std::unordered_set<Point> points;
  while (input >> l) {
    if (!l.is_axial())
      continue;

    for (auto prev : lines) {
      auto section = prev.intersect(l);
      if (!section.has_value())
        continue;

      auto line = section.value();
      for (auto i = line.start.x; i <= line.end.x; i++)
        for (auto j = line.start.y; j <= line.end.y; j++)
          points.emplace(i, j);
    }
    lines.push_back(l);
  }
  std::cerr << "Read " << lines.size() << " axial lines.\n";
  std::cerr << "Unique intersections: " << points.size() << "\n";

  return 0;
}