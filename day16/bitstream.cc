#include "bitstream.h"

#include <iostream>
#include <istream>
#include <utility>

inline uint32_t hex_to_dec(char c) {
  if (isdigit(c))
    return c - '0';
  if (isxdigit(c))
    return c - 'A' + 10;
  throw std::runtime_error("Unexpected character conversion.");
}

Generator<bool> istream_reader(std::istream &s) {
  for (uint32_t v : std::ranges::istream_view<char>(s) | std::ranges::views::transform(hex_to_dec)) {
    co_yield v & 0b1000;
    co_yield v & 0b100;
    co_yield v & 0b10;
    co_yield v & 0b1;
  }
}

BitStream::BitStream(std::istream &input) : gen_(istream_reader(input)), it_(gen_.begin()) {}

std::pair<uint32_t, uint32_t> BitStream::read_bits(uint32_t bit_cnt) {
  if (it_ == gen_.end()) {
    set_done();
    return {0, 0};
  }
  uint32_t result = 0;
  uint32_t read = 0;
  for (auto i = it_; read < bit_cnt && i != gen_.end(); ++i, read++)
    result = (result << 1) | *i;
  return {result, read};
}

SubBitStream::SubBitStream(BaseBitStream &parent, uint32_t bit_limit) : parent_(std::addressof(parent)), limit_(bit_limit) {}

std::pair<uint32_t, uint32_t> SubBitStream::read_bits(uint32_t bit_cnt) {
  if (limit_ == 0) {
    set_done();
    return {0, 0};
  }
  if (bit_cnt > limit_)
    throw std::runtime_error("Attempted to read past limit.");
  auto [data, read] = parent_->read_bits(bit_cnt);
  limit_ -= read;
  return {data, read};
}