#include "point.h"
#include <istream>
#include <ostream>
#include <stdexcept>

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

Point3D Point3D::rotate(const Rotation &rot) const {
  const int64_t *vals[3] = {&x, &y, &z};
  return {(*vals[rot[0].first]) * rot[0].second, (*vals[rot[1].first]) * rot[1].second, (*vals[rot[2].first]) * rot[2].second};
}

Point3D operator-(const Point3D &lhs, const Point3D &rhs) { return {lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z}; }
Point3D operator+(const Point3D &lhs, const Point3D &rhs) { return {lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z}; }