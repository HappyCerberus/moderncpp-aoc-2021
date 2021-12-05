#include "diagonals.h"

#include <istream>
#include <ostream>

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

std::istream &operator>>(std::istream &s, Line &line) {
  if (!s)
    return s;

  if (!(s >> line.start))
    return s;

  char delim1 = 0, delim2 = 0;
  s >> delim1 >> delim2;
  if (delim1 != '-' || delim2 != '>') {
    s.setstate(std::ios_base::badbit);
    return s;
  }

  s >> line.end;
  if (line.is_axial()) {
    if (line.start.x > line.end.x)
      std::swap(line.start.x, line.end.x);
    if (line.start.y > line.end.y)
      std::swap(line.start.y, line.end.y);
  } else {
    if (line.start.x > line.end.x) {
      std::swap(line.start, line.end);
    }
  }
  return s;
}

std::ostream &operator<<(std::ostream &s, const Line &l) {
  s << l.start << " -> " << l.end;
  return s;
}

bool Line::does_intersect(const Line &l) const {
  if (!does_overlay(l))
    return false;
  if (ydir() == -1) {
    return std::max(start.x, l.start.x) <= std::min(end.x, l.end.x) && std::max(end.y, l.end.y) <= std::min(start.y, l.start.y);
  } else {
    return std::max(start.x, l.start.x) <= std::min(end.x, l.end.x) && std::max(start.y, l.start.y) <= std::min(end.y, l.end.y);
  }
}

std::optional<Line> Line::intersect(const Line &l) const {
  if (!does_overlay(l))
    return {};
  if (!does_intersect(l))
    return {};
  if (ydir() == -1) {
    return Line{{std::max(start.x, l.start.x), std::min(start.y, l.start.y)}, {std::min(end.x, l.end.x), std::max(end.y, l.end.y)}};
  } else {
    return Line{{std::max(start.x, l.start.x), std::max(start.y, l.start.y)}, {std::min(end.x, l.end.x), std::min(end.y, l.end.y)}};
  }
}

std::optional<Point> Line::single_point_intersect(const Line &b) const {
  int32_t numerator = b.start.y * xdir() - start.y * xdir() - b.start.x * ydir() + start.x * ydir();
  int32_t denominator = b.xdir() * ydir() - b.ydir() * xdir();
  if (std::abs(denominator) == 2 && numerator % 2 == 1)
    return {};
  if (denominator == 0)
    return {};
  auto n = numerator / denominator;
  auto result = Point{b.start.x + n * b.xdir(), b.start.y + n * b.ydir()};
  if (is_within(result) && b.is_within(result))
    return result;
  return {};
}

bool Line::is_within(Point p) const {
  if (xdir() == 0 && ydir() == 0)
    return start == p;
  if (xdir() == 0) {
    int k = (p.y - start.y) / ydir();
    return k >= 0 && k < length();
  }
  int k = (p.x - start.x) / xdir();
  if (ydir() * k + start.y != p.y)
    return false;
  return k >= 0 && k < length();
}

int32_t Line::xdir() const {
  if (start.x > end.x)
    return -1;
  if (start.x < end.x)
    return 1;
  return 0;
}

int32_t Line::ydir() const {
  if (start.y > end.y)
    return -1;
  if (start.y < end.y)
    return 1;
  return 0;
}

int32_t Line::length() const { return std::max(std::abs(start.x - end.x), std::abs(start.y - end.y)) + 1; }

bool Line::does_overlay(const Line &l) const {
  if (xdir() != l.xdir() || ydir() != l.ydir())
    return false;
  if (is_axial()) {
    if (xdir() == 0 && start.x != l.start.x)
      return false;
    if (ydir() == 0 && start.y != l.start.y)
      return false;
  } else {
    if (start.y - ydir() * start.x != l.start.y - l.ydir() * l.start.x) {
      return false;
    }
  }
  return true;
}