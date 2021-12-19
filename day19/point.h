#ifndef POINT_H_
#define POINT_H_

#include <array>
#include <cstdint>
#include <functional>
#include <iosfwd>

using Rotation = std::array<std::pair<int, int>, 3>;
inline const constexpr int X = 0;
inline const constexpr int Y = 1;
inline const constexpr int Z = 2;
inline const constexpr int POS = 1;
inline const constexpr int NEG = -1;

inline const constexpr std::array<Rotation, 24> ROTATIONS({
    {{{X, POS}, {Y, POS}, {Z, POS}}}, {{{X, POS}, {Z, POS}, {Y, NEG}}}, {{{X, POS}, {Y, NEG}, {Z, NEG}}}, {{{X, POS}, {Z, NEG}, {Y, POS}}},
    {{{X, NEG}, {Y, POS}, {Z, NEG}}}, {{{X, NEG}, {Z, NEG}, {Y, NEG}}}, {{{X, NEG}, {Y, NEG}, {Z, POS}}}, {{{X, NEG}, {Z, POS}, {Y, POS}}},
    {{{Y, POS}, {X, POS}, {Z, NEG}}}, {{{Y, POS}, {Z, NEG}, {X, NEG}}}, {{{Y, POS}, {X, NEG}, {Z, POS}}}, {{{Y, POS}, {Z, POS}, {X, POS}}},
    {{{Y, NEG}, {X, POS}, {Z, POS}}}, {{{Y, NEG}, {Z, POS}, {X, NEG}}}, {{{Y, NEG}, {X, NEG}, {Z, NEG}}}, {{{Y, NEG}, {Z, NEG}, {X, POS}}},
    {{{Z, POS}, {X, POS}, {Y, POS}}}, {{{Z, POS}, {Y, POS}, {X, NEG}}}, {{{Z, POS}, {X, NEG}, {Y, NEG}}}, {{{Z, POS}, {Y, NEG}, {X, POS}}},
    {{{Z, NEG}, {X, POS}, {Y, NEG}}}, {{{Z, NEG}, {Y, NEG}, {X, NEG}}}, {{{Z, NEG}, {X, NEG}, {Y, POS}}}, {{{Z, NEG}, {Y, POS}, {X, POS}}},
});

struct Point3D {
  int64_t x;
  int64_t y;
  int64_t z;
  Point3D rotate(const Rotation &) const;
  int64_t manhattan() { return std::abs(x) + std::abs(y) + std::abs(z); }
  friend std::istream &operator>>(std::istream &, Point3D &);
  friend std::ostream &operator<<(std::ostream &, const Point3D &);
  friend Point3D operator-(const Point3D &, const Point3D &);
  friend Point3D operator+(const Point3D &, const Point3D &);
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