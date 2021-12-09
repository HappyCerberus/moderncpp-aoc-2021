#include "flood-fill.h"

#include <queue>

uint32_t flood_fill(HeightMap &map, uint32_t row, uint32_t column) {
  if (row >= map.size() || column >= map[row].size() || map[row][column] == 9)
    return 0;

  uint32_t result = 0;
  std::queue<std::pair<uint32_t, uint32_t>> queue;
  queue.push(std::make_pair(row, column));
  while (queue.size() != 0) {
    auto [r, c] = queue.front();
    queue.pop();
    if (r + 1 < map.size() && map[r + 1][c] != 9) {
      map[r + 1][c] = 9;
      result++;
      queue.push(std::make_pair(r + 1, c));
    }
    if (r > 0 && map[r - 1][c] != 9) {
      map[r - 1][c] = 9;
      result++;
      queue.push(std::make_pair(r - 1, c));
    }
    if (c + 1 < map[r].size() && map[r][c + 1] != 9) {
      map[r][c + 1] = 9;
      result++;
      queue.push(std::make_pair(r, c + 1));
    }
    if (c > 0 && map[r][c - 1] != 9) {
      map[r][c - 1] = 9;
      result++;
      queue.push(std::make_pair(r, c - 1));
    }
  }
  return result;
}