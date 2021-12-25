#include "seabed.h"

#include <algorithm>
#include <istream>
#include <string>

SeaBed parse_seabed(std::istream &s) {
  SeaBed result;
  std::string line;
  while (getline(s, line)) {
    result.push_back(std::vector<char>(line.begin(), line.end()));
  }
  return result;
}

std::pair<SeaBed, size_t> tick(const SeaBed &input) {
  std::pair<SeaBed, size_t> result{input, 0};
  for (size_t i = 0; i < input.size(); i++) {
    for (size_t j = 0; j < input[i].size(); j++) {
      size_t src = (j + input[i].size() - 1) % input[i].size();
      if (input[i][j] == '.' && input[i][src] == '>') {
        result.first[i][j] = '>';
        result.first[i][src] = '.';
        result.second++;
      }
    }
  }
  for (size_t i = 0; i < input.size(); i++) {
    for (size_t j = 0; j < input[i].size(); j++) {
      size_t src = (i + input.size() - 1) % input.size();
      if (result.first[i][j] == '.' && input[i][j] != 'v' && input[src][j] == 'v') {
        result.first[i][j] = 'v';
        result.first[src][j] = '.';
        result.second++;
      }
    }
  }
  return result;
}

std::ostream &operator<<(std::ostream &s, const SeaBed &bed) {
  for (auto &row : bed) {
    std::ranges::copy(row, std::ostreambuf_iterator(s));
    s << "\n";
  }
  return s;
}
