#include "point.h"

#include <istream>
#include <ostream>

std::istream &operator>>(std::istream &s, Point3D &b) {
  char delim;
  int coord;

  if (!(s >> coord)) {
    return s;
  }
  b.x = coord;

  if (!(s >> delim) || delim != ',')
    throw std::runtime_error("Found unexpected delimiter.");

  if (!(s >> b.y >> delim >> b.z) || delim != ',')
    throw std::runtime_error("Failed to parse y and z coordinates.");
  return s;
}

std::ostream &operator<<(std::ostream &s, const Point3D &b) {
  s << b.x << "," << b.y << "," << b.z;
  return s;
}