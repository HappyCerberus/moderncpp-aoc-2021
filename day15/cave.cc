#include "cave.h"
#include <deque>
#include <iostream>
#include <istream>
#include <limits>
#include <queue>

Cave parse_cave(std::istream &input) {
  Cave result;
  std::vector<uint8_t> line;
  char c;

  input.unsetf(std::ios_base::skipws);
  while (input >> c) {
    if (c == '\n') {
      result.emplace_back(move(line));
    } else if (std::isdigit(c)) {
      line.push_back(c - '0');
    }
  }
  if (line.size() > 0)
    result.emplace_back(std::move(line));

  return result;
}

Cave expand_cave(const Cave &cave) {
  const size_t dim = cave.size();
  std::vector<std::vector<uint8_t>> result(dim * 5, std::vector<uint8_t>(dim * 5, 0));
  for (size_t i = 0; i < result.size(); i++) {
    for (size_t j = 0; j < result[i].size(); j++) {
      result[i][j] = (((cave[i % dim][j % dim] + i / dim + j / dim) - 1) % 9) + 1;
    }
  }
  return result;
}

size_t least_path_cost(const Cave &cave) {
  std::vector<std::vector<size_t>> cost(cave.size(), std::vector<size_t>(cave.size(), std::numeric_limits<size_t>::max()));
  cost[0][0] = 0;

  std::deque<std::pair<size_t, size_t>> pending;
  pending.push_back({0, 0});

  while (!pending.empty()) {
    auto [row, col] = pending.front();
    pending.pop_front();

    if (row > 0 && cost[row][col] + cave[row - 1][col] < cost[row - 1][col]) {
      cost[row - 1][col] = cost[row][col] + cave[row - 1][col];
      pending.push_back({row - 1, col});
    }
    if (row + 1 < cost.size() && cost[row][col] + cave[row + 1][col] < cost[row + 1][col]) {
      cost[row + 1][col] = cost[row][col] + cave[row + 1][col];
      pending.push_back({row + 1, col});
    }
    if (col > 0 && cost[row][col] + cave[row][col - 1] < cost[row][col - 1]) {
      cost[row][col - 1] = cost[row][col] + cave[row][col - 1];
      pending.push_back({row, col - 1});
    }
    if (col + 1 < cost[row].size() && cost[row][col] + cave[row][col + 1] < cost[row][col + 1]) {
      cost[row][col + 1] = cost[row][col] + cave[row][col + 1];
      pending.push_back({row, col + 1});
    }
  }

  return cost[cost.size() - 1][cost[cost.size() - 1].size() - 1];
}

struct Point {
  size_t row;
  size_t col;
  size_t cost;
  friend auto operator<=>(const Point &l, const Point &r) { return l.cost <=> r.cost; }
};

size_t least_path_cost_fast(const Cave &cave) {
  std::vector<std::vector<size_t>> cost(cave.size(), std::vector<size_t>(cave.size(), std::numeric_limits<size_t>::max()));
  cost[0][0] = 0;

  std::priority_queue<Point, std::vector<Point>, std::greater<>> pq;
  pq.push({0, 0, 0});

  while (!pq.empty()) {
    auto point = pq.top();
    pq.pop();
    if (point.cost > cost[point.row][point.col])
      continue;
    auto row = point.row;
    auto col = point.col;

    if (row > 0 && cost[row][col] + cave[row - 1][col] < cost[row - 1][col]) {
      cost[row - 1][col] = cost[row][col] + cave[row - 1][col];
      pq.push({row - 1, col, cost[row - 1][col]});
    }
    if (row + 1 < cost.size() && cost[row][col] + cave[row + 1][col] < cost[row + 1][col]) {
      cost[row + 1][col] = cost[row][col] + cave[row + 1][col];
      pq.push({row + 1, col, cost[row + 1][col]});
    }
    if (col > 0 && cost[row][col] + cave[row][col - 1] < cost[row][col - 1]) {
      cost[row][col - 1] = cost[row][col] + cave[row][col - 1];
      pq.push({row, col - 1, cost[row][col - 1]});
    }
    if (col + 1 < cost[row].size() && cost[row][col] + cave[row][col + 1] < cost[row][col + 1]) {
      cost[row][col + 1] = cost[row][col] + cave[row][col + 1];
      pq.push({row, col + 1, cost[row][col + 1]});
    }
  }

  return cost[cost.size() - 1][cost[cost.size() - 1].size() - 1];
}