#include "scanner.h"

#include <algorithm>
#include <deque>
#include <iostream>
#include <istream>
#include <ostream>
#include <ranges>
#include <sstream>
#include <string>
#include <unordered_set>

std::istream &operator>>(std::istream &s, Scanner &scan) {
  std::string line;
  std::string_view header = "--- scanner ";
  std::stringstream parse;
  scan.beacons.clear();
  while (getline(s, line)) {
    if (line == "")
      break;
    if (line.starts_with(header)) {
      scan.scanner_id = std::stoll(line.substr(header.length()));
      continue;
    }
    parse.clear();
    parse.str(line);
    Beacon b;
    if (parse >> b)
      scan.beacons.push_back(b);
    else
      return s;
  }
  return s;
}

std::ostream &operator<<(std::ostream &s, const Scanner &scan) {
  s << "--- scanner " << scan.scanner_id << " ---\n";
  std::ranges::copy(scan.beacons, std::ostream_iterator<Beacon>(s, "\n"));
  return s;
}

std::optional<ScannerOrientation> Scanner::overlaps(const Scanner &other, uint64_t threshold) const {
  for (auto &rotation : ROTATIONS) {
    std::unordered_map<Beacon, uint32_t> cnts;
    for (auto &lhs : beacons)
      for (auto &rhs : other.beacons)
        cnts[lhs - rhs.rotate(rotation)]++;

    for (auto &el : cnts)
      if (el.second >= threshold)
        return ScannerOrientation{rotation, el.first};
  }
  return {};
}

void Scanner::normalize(const ScannerOrientation &orientation) {
  for (auto &beacon : beacons)
    beacon = beacon.rotate(orientation.rotation) + orientation.position;
  position = orientation.position;
}

void normalize_scanners(std::vector<Scanner> &scanners, uint64_t threshold) {
  std::unordered_set<int64_t> fixed;
  std::deque<int64_t> queue;
  fixed.insert(0);
  queue.push_back(0);
  scanners[0].position = Point3D{0, 0, 0};
  while (!queue.empty()) {
    auto tested = queue.front();
    queue.pop_front();
    for (size_t other = 0; other < scanners.size(); other++) {
      if (fixed.contains(other))
        continue;
      auto rot = scanners[tested].overlaps(scanners[other], threshold);
      if (!rot.has_value())
        continue;
      scanners[other].normalize(rot.value());
      queue.push_back(other);
      fixed.insert(other);
    }
  }
}