#ifndef POINT3D_H_
#define POINT3D_H_

#include <cstdint>
#include <functional>
#include <iosfwd>

struct Point3D {
  int64_t x;
  int64_t y;
  int64_t z;
  friend std::istream &operator>>(std::istream &, Point3D &);
  friend std::ostream &operator<<(std::ostream &, const Point3D &);
  friend auto operator<=>(const Point3D &, const Point3D &) = default;
};

template <> struct std::hash<Point3D> {
  std::size_t operator()(Point3D const &s) const noexcept {
    std::size_t h1 = std::hash<int64_t>{}(s.x);
    std::size_t h2 = std::hash<int64_t>{}(s.y);
    std::size_t h3 = std::hash<int64_t>{}(s.z);
    return h1 ^ (h2 << 1) ^ (h3 << 2); // or use boost::hash_combine
  }
};

#endif