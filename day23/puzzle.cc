#include "puzzle.h"

#include <algorithm>
#include <ostream>

size_t distance(size_t from, size_t to) {
  if (to > from)
    return to - from;
  else
    return from - to;
}

size_t Puzzle::greedy_move_to_room() {
  for (size_t i = 0; i < hallway.size(); i++) {
    char who = hallway[i];
    if (who == '.')
      continue;
    if (!rooms[who - 'A'].can_accept())
      continue;
    size_t target = 2 + 2 * (who - 'A');
    if (occupied_spaces_between(i, target) > 1)
      continue;
    size_t cost = rooms[who - 'A'].push(who);
    hallway[i] = '.';
    return cost + COST.at(who) * distance(i, target);
  }
  return 0;
}

size_t Puzzle::greedy_room_to_room() {
  for (size_t h = 0; h < rooms.size(); h++) {
    if (!rooms[h].has_visitors())
      continue;
    char who = rooms[h].top();
    if (!rooms[who - 'A'].can_accept())
      continue;
    if (occupied_spaces_between(2 * h + 2, 2 * (who - 'A') + 2) != 0)
      continue;
    size_t cost = rooms[h].pop();
    cost += rooms[who - 'A'].push(who);
    cost += distance(h, who - 'A') * 2 * COST.at(who);
    return cost;
  }
  return 0;
}

size_t Puzzle::occupied_spaces_between(size_t from, size_t to) const {
  auto b = hallway.begin() + std::min(from, to);
  auto e = hallway.begin() + std::max(from, to) + 1;
  return std::ranges::count_if(b, e, [](auto c) { return c != '.'; });
}

bool Puzzle::solved() const {
  for (auto &room : rooms)
    if (!room.is_finished())
      return false;
  return true;
}

std::optional<size_t> Puzzle::hallway_move(size_t room, size_t target) {
  // check the room
  if (!rooms[room].has_visitors())
    return {};
  // don't land in front of rooms
  if (target % 2 == 0 && target != 0 && target != 10)
    return {};
  size_t source = room * 2 + 2;
  if (occupied_spaces_between(source, target) != 0)
    return {};

  char who = rooms[room].top();
  size_t cost = distance(source, target) * COST.at(who);
  cost += rooms[room].pop();
  hallway[target] = who;

  return cost;
}

std::optional<size_t> find_shortest(Puzzle puzzle) {
  size_t cost = 0;
  while (true) {
    size_t greedy = puzzle.greedy_move_to_room();
    greedy += puzzle.greedy_room_to_room();
    if (greedy == 0)
      break;
    cost += greedy;
  }

  if (puzzle.solved()) {
    return cost;
  }

  size_t best = std::numeric_limits<size_t>::max();
  for (size_t h = 0; h < puzzle.rooms.size(); h++) {
    if (!puzzle.rooms[h].has_visitors())
      continue;
    for (size_t i = 0; i < puzzle.hallway.size(); i++) {
      if (i % 2 == 0 && i != 0 && i != 10)
        continue;
      if (puzzle.occupied_spaces_between(h * 2 + 2, i) != 0)
        continue;
      Puzzle copy = puzzle;
      auto move_cost = copy.hallway_move(h, i);
      if (!move_cost.has_value())
        continue;
      auto recursion = find_shortest(std::move(copy));
      if (!recursion.has_value())
        continue;
      best = std::min(best, move_cost.value() + recursion.value());
    }
  }
  if (best == std::numeric_limits<size_t>::max())
    return {};

  return best + cost;
}

std::ostream &operator<<(std::ostream &s, const Puzzle &puzzle) {
  for (size_t i = 0; i < puzzle.hallway.size() + 2; i++)
    s << "#";
  s << "\n";

  s << "#";
  for (size_t i = 0; i < puzzle.hallway.size(); i++)
    s << puzzle.hallway[i];
  s << "#\n";

  s << "###";
  for (size_t i = 0; i < puzzle.rooms.size(); i++)
    s << puzzle.rooms[i].at(1) << "#";
  s << "##\n";

  s << "  #";
  for (size_t i = 0; i < puzzle.rooms.size(); i++)
    s << puzzle.rooms[i].at(0) << "#";
  s << "\n";

  s << "  ";
  for (size_t i = 0; i < puzzle.hallway.size() - 2; i++)
    s << "#";
  s << "\n";

  return s;
}