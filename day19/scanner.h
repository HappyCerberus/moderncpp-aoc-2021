#ifndef SCANNER_H_
#define SCANNER_H_

#include <optional>
#include <vector>

#include "point.h"
using Beacon = Point3D;

struct ScannerOrientation {
  Rotation rotation;
  Point3D position;
};

struct Scanner {
  int64_t scanner_id;
  std::vector<Beacon> beacons;
  Point3D position;

  std::optional<ScannerOrientation> overlaps(const Scanner &other, uint64_t threshold) const;
  void normalize(const ScannerOrientation &);

  friend std::istream &operator>>(std::istream &, Scanner &);
  friend std::ostream &operator<<(std::ostream &, const Scanner &);
};

void normalize_scanners(std::vector<Scanner> &scanners, uint64_t threshold);

#endif