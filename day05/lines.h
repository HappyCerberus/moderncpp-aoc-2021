#ifndef LINES_H_
#define LINES_H_

#include <algorithm>
#include <cstdint>
#include <iosfwd>
#include <optional>

struct Point {
  int32_t x;
  int32_t y;
  friend std::istream &operator>>(std::istream &, Point &);
  friend std::ostream &operator<<(std::ostream &, const Point &);
  friend auto operator<=>(const Point &, const Point &) = default;
};

template <> struct std::hash<Point> {
  std::size_t operator()(Point const &s) const noexcept {
    std::size_t h1 = std::hash<int32_t>{}(s.x);
    std::size_t h2 = std::hash<int32_t>{}(s.y);
    return h1 ^ (h2 << 1); // or use boost::hash_combine
  }
};

struct Line {
  Point start;
  Point end;
  bool is_axial() const { return start.x == end.x || start.y == end.y; }
  bool does_intersect(const Line &l) const;
  std::optional<Line> intersect(const Line &l) const;
  friend std::istream &operator>>(std::istream &, Line &);
  friend std::ostream &operator<<(std::ostream &, const Line &);
  friend auto operator<=>(const Line &, const Line &) = default;
};

#endif