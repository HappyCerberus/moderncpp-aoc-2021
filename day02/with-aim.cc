#include "with-aim.h"

#include <istream>

Position navigate(std::istream &s) {
  std::string line;
  Position result = {.depth = 0, .distance = 0, .aim = 0};
  while (std::getline(s, line)) {
    navigate(result, line);
  }

  return result;
}

void navigate(Position &position, const std::string &line) {
  if (auto pos = line.find_first_of(' '); pos != std::string::npos) {
    int number = std::stoi(line.substr(pos + 1));
    if (line.starts_with("forward")) {
      position.forward(number);
    } else if (line.starts_with("down")) {
      position.down(number);
    } else if (line.starts_with("up")) {
      position.up(number);
    }
  }
}