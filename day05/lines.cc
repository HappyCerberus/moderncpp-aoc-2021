#include "lines.h"

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
  if (line.start.x > line.end.x) {
    std::swap(line.start.x, line.end.x);
  }
  if (line.start.y > line.end.y) {
    std::swap(line.start.y, line.end.y);
  }
  return s;
}

std::ostream &operator<<(std::ostream &s, const Line &l) {
  s << l.start << " -> " << l.end;
  return s;
}

bool Line::does_intersect(const Line &l) const {
  return std::max(start.x, l.start.x) <= std::min(end.x, l.end.x) && std::max(start.y, l.start.y) <= std::min(end.y, l.end.y);
}

std::optional<Line> Line::intersect(const Line &l) const {
  if (!does_intersect(l))
    return {};
  return Line{{std::max(start.x, l.start.x), std::max(start.y, l.start.y)}, {std::min(end.x, l.end.x), std::min(end.y, l.end.y)}};
}
