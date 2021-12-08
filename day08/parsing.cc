#include "parsing.h"
#include <ctype.h>
#include <stdexcept>

Puzzle parse_line(const std::string &input) {
  Puzzle result;
  bool past_delim = false;
  auto it = input.begin();
  while (it != input.end()) {
    // read one number
    Display d = 0;
    while (it != input.end() && std::islower(*it)) {
      if (*it - 'a' > 7)
        throw std::out_of_range("Unexpected value in input, only accepts values 'a-g'.");
      d |= 1 << (*it - 'a');
      it++;
    }
    if (past_delim) {
      result.numbers.push_back(d);
    } else {
      result.patterns.push_back(d);
    }
    // skip over spaces and delimiter '|'
    while (it != input.end() && (std::isspace(*it) || *it == '|')) {
      if (*it == '|')
        past_delim = true;
      it++;
    }
  }
  return result;
}