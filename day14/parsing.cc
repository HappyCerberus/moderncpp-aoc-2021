#include "parsing.h"
#include <istream>

std::pair<std::string, InsertionRules> parse_rules(std::istream &input) {
  std::string start;
  if (!(input >> start))
    throw std::runtime_error("Failed to parse input is empty.");

  InsertionRules rules;
  std::string pair, delim, result;
  while (input >> pair >> delim >> result) {
    if (delim != "->")
      throw std::runtime_error("Failed to parse input, did not find expected delimiter.");
    if (pair.length() < 2 || result.length() == 0)
      throw std::runtime_error("Failed to parse input, malformed rule.");
    rules.emplace(Pair{pair[0], pair[1]}, result[0]);
  }
  return {start, rules};
}