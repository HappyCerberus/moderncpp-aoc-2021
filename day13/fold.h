#ifndef FOLD_H_
#define FOLD_H_

#include <cstdint>
#include <functional>
#include <iosfwd>
#include <unordered_set>
#include <vector>

struct Point {
  uint32_t x;
  uint32_t y;
  friend std::istream &operator>>(std::istream &, Point &);
  friend std::ostream &operator<<(std::ostream &, const Point &);
  friend auto operator<=>(const Point &, const Point &) = default;
};

template <> struct std::hash<Point> {
  std::size_t operator()(Point const &s) const noexcept {
    std::size_t h1 = std::hash<uint32_t>{}(s.x);
    std::size_t h2 = std::hash<uint32_t>{}(s.y);
    return h1 ^ (h2 << 1); // or use boost::hash_combine
  }
};

uint32_t fold_number(uint32_t number, uint32_t fold_point);

using Points = std::unordered_set<Point>;

struct Fold {
  enum {
    X_FOLD,
    Y_FOLD,
  } direction;
  uint32_t number;
};
using Folds = std::vector<Fold>;

struct Paper {
  Points points;
  Folds folds;
  friend std::ostream &operator<<(std::ostream &, const Paper &);
};

Paper parse_input(std::istream &);
uint32_t fold_number(uint32_t number, uint32_t fold_point);
void first_fold(Paper &);

void fold_paper(Paper &);

#endif