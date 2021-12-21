#include <algorithm>
#include <iostream>
#include <ranges>
#include <string>
#include <unordered_map>

uint32_t ordinal_mod(uint32_t value, uint32_t max) { return (value - 1) % max + 1; }

std::unordered_map<uint32_t, uint32_t> distribution = {{3, 1}, {4, 3}, {5, 6}, {6, 7}, {7, 6}, {8, 3}, {9, 1}};

struct Player {
  uint64_t score;
  uint64_t position;
  friend auto operator<=>(const Player &, const Player &) = default;
};

template <> struct std::hash<Player> {
  std::size_t operator()(Player const &p) const noexcept {
    std::size_t h1 = std::hash<int64_t>{}(p.score);
    std::size_t h2 = std::hash<int64_t>{}(p.position);
    return h1 ^ (h2 << 1); // or use boost::hash_combine
  }
};

struct State {
  Player player1;
  Player player2;
  friend auto operator<=>(const State &, const State &) = default;
};

template <> struct std::hash<State> {
  std::size_t operator()(State const &s) const noexcept {
    std::size_t h1 = std::hash<Player>{}(s.player1);
    std::size_t h2 = std::hash<Player>{}(s.player2);
    return h1 ^ (h2 << 1); // or use boost::hash_combine
  }
};

std::unordered_map<State, std::pair<uint64_t, uint64_t>> cache;

std::pair<uint64_t, uint64_t> cnt_wins(uint64_t player1_score, uint64_t player2_score, uint64_t player1_pos, uint64_t player2_pos, bool player1_turn) {
  if (player1_turn) {
    if (player2_score >= 21)
      return {0, 1};
    State s{.player1 = {player1_score, player1_pos}, .player2 = {player2_score, player2_pos}};
    if (cache.contains(s)) {
      return cache[s];
    }
  } else {
    if (player1_score >= 21)
      return {1, 0};
    State s{.player1 = {player2_score, player2_pos}, .player2 = {player1_score, player1_pos}};
    auto cached = cache.find(s);
    if (cached != cache.end()) {
      return {cached->second.second, cached->second.first};
    }
  }

  if (player1_turn) {
    std::pair<uint64_t, uint64_t> sum = {0, 0};
    for (auto [roll, cnt] : distribution) {
      uint64_t new_pos = ordinal_mod(player1_pos + roll, 10);
      auto [p1, p2] = cnt_wins(player1_score + new_pos, player2_score, new_pos, player2_pos, false);
      sum.first += cnt * p1;
      sum.second += cnt * p2;
    }
    State s{.player1 = {player1_score, player1_pos}, .player2 = {player2_score, player2_pos}};
    cache.insert(std::make_pair(s, sum));
    return sum;
  } else {
    std::pair<uint64_t, uint64_t> sum = {0, 0};
    for (auto [roll, cnt] : distribution) {
      uint64_t new_pos = ordinal_mod(player2_pos + roll, 10);
      auto [p1, p2] = cnt_wins(player1_score, player2_score + new_pos, player1_pos, new_pos, true);
      sum.first += cnt * p1;
      sum.second += cnt * p2;
    }
    State s{.player1 = {player2_score, player2_pos}, .player2 = {player1_score, player1_pos}};
    cache.insert(std::make_pair(s, std::make_pair(sum.second, sum.first)));
    return sum;
  }
}

int main() {
  auto [p1, p2] = cnt_wins(0, 0, 4, 2, true);
  std::cout << "Player 1 wins in " << p1 << " universes.\n"
            << "Player 2 wins in " << p2 << " universes.\n";
}