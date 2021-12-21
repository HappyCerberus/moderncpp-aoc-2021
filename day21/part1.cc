#include <algorithm>
#include <iostream>
#include <ranges>
#include <string>
#include <unordered_map>

uint32_t ordinal_mod(uint32_t value, uint32_t max) { return (value - 1) % max + 1; }

template <uint32_t sides> uint32_t dice() {
  static uint32_t value = 0;
  return value = ordinal_mod(value + 1, sides);
}

uint32_t turn(uint32_t position) { return ordinal_mod(position + dice<100>() + dice<100>() + dice<100>(), 10); }

int main() {
  uint32_t player1 = 4, player1_score = 0, player2 = 2, player2_score = 0;
  uint32_t rolls = 0;

  while (true) {
    player1_score += (player1 = turn(player1));
    rolls += 3;
    if (player1_score >= 1000) {
      std::cout << "Game ends, player 1 wins with " << player1_score << " player2 loses with " << player2_score << " dice was rolled " << rolls << " times ("
                << rolls * player2_score << ").\n";
      return 0;
    }
    player2_score += (player2 = turn(player2));
    rolls += 3;
    if (player2_score >= 1000) {
      std::cout << "Game ends, player 2 wins with " << player2_score << " player1 loses with " << player1_score << " dice was rolled " << rolls << " times ("
                << rolls * player1_score << ").\n";
      return 0;
    }
  }
}