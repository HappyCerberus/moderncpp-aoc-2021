#ifndef PUZZLE_H_
#define PUZZLE_H_

#include "room.h"

#include <iosfwd>
#include <limits>
#include <optional>
#include <vector>

struct Puzzle {
  std::vector<char> hallway;
  std::vector<Room> rooms;

  size_t greedy_move_to_room();
  size_t greedy_room_to_room();
  std::optional<size_t> hallway_move(size_t home, size_t pos);
  size_t occupied_spaces_between(size_t from, size_t to) const;
  bool solved() const;

  friend std::ostream &operator<<(std::ostream &, const Puzzle &);
};

std::optional<size_t> find_shortest(Puzzle puzzle);

#endif