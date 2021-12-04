#ifndef BINGO_H_
#define BINGO_H_

#include <cstdint>
#include <iosfwd>
#include <string>
#include <unordered_map>
#include <vector>

struct State {
  std::vector<uint32_t> rows_and_columns;
  std::unordered_map<uint32_t, std::vector<std::size_t>> number_positions;
  std::vector<uint32_t> board_sums;
};

std::size_t process_draws(State &, const std::string &input);
std::size_t process_draws_until_last(State &, const std::string &input);

std::istream &operator>>(std::istream &, State &);

#endif