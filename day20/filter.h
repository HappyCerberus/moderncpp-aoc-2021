#ifndef FILTER_H_
#define FILTER_H_

#include <cstdint>
#include <iosfwd>
#include <vector>

struct Image {
  std::vector<bool> decoder;
  std::vector<std::vector<bool>> data;
  bool default_value = false;

  uint32_t encoded_number(int64_t line, int64_t column) const;
  void enhance();
  uint32_t lit_pixels() const;

  friend std::istream &operator>>(std::istream &, Image &);
  friend std::ostream &operator<<(std::ostream &, const Image &);
};

#endif