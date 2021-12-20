#include "filter.h"

#include <algorithm>
#include <istream>
#include <limits>
#include <ostream>
#include <ranges>

uint32_t Image::encoded_number(int64_t line, int64_t column) const {
  uint32_t result = 0;
  for (int64_t i = line - 1; i <= line + 1; i++)
    for (int64_t j = column - 1; j <= column + 1; j++)
      if (i >= 0 && i < std::ranges::ssize(data) && j >= 0 && j < std::ranges::ssize(data[i]))
        result = (result << 1) | data[i][j];
      else
        result = (result << 1) | default_value;

  return result;
}

void Image::enhance() {
  std::vector<std::vector<bool>> new_data(data.size() + 2, std::vector<bool>(data.size() + 2, false));
  for (int64_t i = -1; i <= std::ranges::ssize(data); i++)
    for (int64_t j = -1; j <= std::ranges::ssize(data[0]); j++)
      new_data[i + 1][j + 1] = decoder[encoded_number(i, j)];

  default_value = default_value ? decoder[0b111111111] : decoder[0];
  std::swap(data, new_data);
}

uint32_t Image::lit_pixels() const {
  uint32_t lit = 0;
  if (default_value)
    return std::numeric_limits<uint32_t>::max();

  for (auto &line : data)
    lit += std::ranges::count(line, true);
  return lit;
}

std::istream &operator>>(std::istream &s, Image &image) {
  s >> std::noskipws;
  auto line_view = std::ranges::istream_view<char>(s) | std::views::drop_while(isspace) | std::ranges::views::take_while([](char c) { return c != '\n'; }) |
                   std::ranges::views::transform([](char c) { return c == '#'; });
  std::ranges::copy(line_view, std::back_insert_iterator(image.decoder));
  while (!s.eof()) {
    std::vector<bool> line;
    std::ranges::copy(line_view, std::back_insert_iterator(line));
    image.data.emplace_back(std::move(line));
  }
  return s;
}

std::ostream &operator<<(std::ostream &s, const Image &image) {
  auto visual = std::views::transform([](bool b) { return b ? '#' : '.'; });
  std::ranges::copy(image.decoder | visual, std::ostream_iterator<char>(s));
  s << "\n\n";
  for (auto &line : image.data) {
    std::ranges::copy(line | visual, std::ostream_iterator<char>(s));
    s << "\n";
  }
  return s;
}