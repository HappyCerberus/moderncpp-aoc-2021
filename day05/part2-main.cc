#include <fstream>
#include <iostream>
#include <unordered_set>
#include <vector>

#include "diagonals.h"

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
    for (auto prev : lines) {
      if (prev.does_overlay(l)) {
        auto section = prev.intersect(l);
        if (!section.has_value())
          continue;

        Line line = section.value();
        auto point = line.start;
        points.insert(point);
        if (point != line.end)
          do {
            point.x += line.xdir();
            point.y += line.ydir();
            points.insert(point);
          } while (point != line.end);
      } else {
        auto point = prev.single_point_intersect(l);
        if (point) {
          points.insert(point.value());
        }
      }
    }
    lines.push_back(l);
  }
  std::cerr << "Read " << lines.size() << " lines.\n";
  std::cerr << "Unique intersections: " << points.size() << "\n";

  return 0;
}