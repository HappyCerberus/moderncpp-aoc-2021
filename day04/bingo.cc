#include "bingo.h"

#include <iostream>
#include <sstream>
#include <unordered_set>

std::size_t process_draws(State &state, const std::string &input) {
  std::stringstream sin(input);
  uint32_t draw = 0;
  while (sin >> draw) {
    char skip_delim;
    sin >> skip_delim; // this can fail
    if (!state.number_positions.contains(draw))
      continue;
    for (auto pos : state.number_positions[draw]) {
      state.board_sums[pos / 10] -= draw;
    }
    for (auto pos : state.number_positions[draw]) {
      state.rows_and_columns[pos]--;
      if (state.rows_and_columns[pos] == 0) {
        return draw * state.board_sums[pos / 10] / 2;
      }
    }
  }
  throw std::runtime_error("No one wins.");
}

std::size_t process_draws_until_last(State &state, const std::string &input) {
  std::unordered_set<uint32_t> boards_that_won;
  std::stringstream sin(input);
  uint32_t draw = 0;
  while (sin >> draw) {
    char skip_delim;
    sin >> skip_delim; // this can fail
    if (!state.number_positions.contains(draw))
      continue;
    for (auto pos : state.number_positions[draw]) {
      state.board_sums[pos / 10] -= draw;
    }
    for (auto pos : state.number_positions[draw]) {
      state.rows_and_columns[pos]--;
      if (state.rows_and_columns[pos] == 0) {
        boards_that_won.insert(pos / 10);
        if (boards_that_won.size() == state.board_sums.size())
          return draw * state.board_sums[pos / 10] / 2;
      }
    }
  }
  throw std::runtime_error("No one wins.");
}

std::istream &operator>>(std::istream &s, State &state) {
  uint32_t board_id = 0;
  uint32_t board_sum = 0;
  while (true) {
    for (int i = 0; i < 25; i++) {
      uint32_t num = 0;
      if (!(s >> num)) {
        if (i != 0) // error in the middle of a board
          throw std::runtime_error("Failed to read the board number " + std::to_string(board_id + 1));
        return s; // done reading
      }
      auto [it, fresh] = state.number_positions.insert(make_pair(num, std::vector<std::size_t>{}));
      it->second.push_back(board_id * 10 + i / 5);     // row
      it->second.push_back(board_id * 10 + 5 + i % 5); // column
      board_sum += num;
    }
    // 5 rows and 5 columns each with 5 numbers
    for (int i = 0; i < 10; i++)
      state.rows_and_columns.push_back(5);
    state.board_sums.push_back(board_sum * 2);
    board_sum = 0;
    board_id++;
  }
  return s;
}