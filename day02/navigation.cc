#include "navigation.h"

#include <istream>

Position navigate(const std::string &line) {
  if (auto pos = line.find_first_of(' '); pos != std::string::npos) {
    int number = std::stoi(line.substr(pos + 1));
    if (line.starts_with("forward")) {
      return {.depth = 0, .distance = number};
    } else if (line.starts_with("down")) {
      return {.depth = number, .distance = 0};
    } else if (line.starts_with("up")) {
      return {.depth = number * -1, .distance = 0};
    }
  }
  return {};
}

Position navigate(std::istream &s) {
  std::string line;
  Position result = {.depth = 0, .distance = 0};
  while (std::getline(s, line)) {
    result += navigate(line);
  }

  return result;
}