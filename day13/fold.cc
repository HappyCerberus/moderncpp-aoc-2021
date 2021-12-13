#include "fold.h"

#include <algorithm>
#include <cstring>
#include <iostream>
#include <iterator>
#include <ranges>
#include <stdexcept>

uint32_t fold_number(uint32_t number, uint32_t fold_point) {
  if (number <= fold_point)
    return number;
  if (number - fold_point > fold_point)
    throw std::out_of_range("Folded number would be negative.");
  return fold_point - (number - fold_point);
}

std::istream &operator>>(std::istream &s, Point &p) {
  if (!s)
    return s;

  if (!(s >> p.x))
    return s;

  char delim = 0;
  s >> delim;
  if (delim != ',') {
    s.setstate(std::ios_base::badbit);
    return s;
  }

  s >> p.y;

  return s;
}

std::ostream &operator<<(std::ostream &s, const Point &p) {
  s << p.x << "," << p.y;
  return s;
}

Paper parse_input(std::istream &s) {
  Paper result;

  Point p;
  while (s >> p)
    result.points.insert(p);
  s.clear();

  std::string line;
  std::string_view xfold_text = "fold along x=";
  std::string_view yfold_text = "fold along y=";
  while (getline(s, line)) {
    if (line.starts_with(xfold_text)) {
      uint32_t number = stoi(line.substr(xfold_text.length()));
      result.folds.emplace_back(Fold::X_FOLD, number);
    } else if (line.starts_with(yfold_text)) {
      uint32_t number = stoi(line.substr(yfold_text.length()));
      result.folds.emplace_back(Fold::Y_FOLD, number);
    }
  }
  return result;
}

void first_fold(Paper &input) {
  std::unordered_set<Point> new_points;
  std::ranges::transform(input.points, std::inserter(new_points, new_points.end()), [fold = input.folds[0]](Point p) {
    if (fold.direction == Fold::X_FOLD) {
      return Point{fold_number(p.x, fold.number), p.y};
    } else {
      return Point{p.x, fold_number(p.y, fold.number)};
    }
  });
  input.points = std::move(new_points);
}

void fold_paper(Paper &input) {
  for (auto &fold : input.folds) {
    std::unordered_set<Point> new_points;
    std::ranges::transform(input.points, std::inserter(new_points, new_points.end()), [fold](Point p) {
      if (fold.direction == Fold::X_FOLD) {
        return Point{fold_number(p.x, fold.number), p.y};
      } else {
        return Point{p.x, fold_number(p.y, fold.number)};
      }
    });
    input.points = std::move(new_points);
  }
}

std::ostream &operator<<(std::ostream &s, const Paper &paper) {
  auto xfilter = paper.folds | std::views::filter([](auto fold) { return fold.direction == Fold::X_FOLD; });
  auto max_x = std::ranges::min_element(xfilter, {}, &Fold::number);
  auto yfilter = paper.folds | std::views::filter([](auto fold) { return fold.direction == Fold::Y_FOLD; });
  auto max_y = std::ranges::min_element(yfilter, {}, &Fold::number);
  
  std::vector<std::string> display(max_y->number, std::string(max_x->number, ' '));
  for (auto &p : paper.points) {
    display[p.y][p.x] = '#';
  }

  for (auto &l : display) {
    s << l << "\n";
  }
  return s;
}
