#ifndef BITSTREAM_H_
#define BITSTREAM_H_

#include "generator.h"
#include <algorithm>
#include <climits>
#include <concepts>
#include <cstdint>
#include <iosfwd>
#include <iostream>
#include <optional>
#include <ranges>
#include <stdexcept>
#include <utility>

uint32_t hex_to_dec(char c);
Generator<bool> istream_reader(std::istream &s);

struct field_width_mod {
  uint8_t width;
};
inline const constexpr auto field_width = [](uint8_t width) { return field_width_mod{width}; };

struct BaseBitStream {
  BaseBitStream() : next_field_{}, done_(false) {}
  explicit operator bool() const { return !done_; }
  virtual std::pair<uint32_t, uint32_t> read_bits(uint32_t bit_cnt) = 0;

  friend BaseBitStream &operator>>(BaseBitStream &s, field_width_mod mod) {
    s.next_field_ = mod.width;
    return s;
  }

  friend BaseBitStream &operator>>(BaseBitStream &s, std::integral auto &value) {
    auto width = sizeof(value) * CHAR_BIT;
    if (s.next_field_.has_value()) {
      width = s.next_field_.value();
    }
    auto [data, cnt] = s.read_bits(width);
    if (cnt != width)
      return s;
    value = data;
    s.next_field_ = std::optional<uint8_t>();
    return s;
  }

  void set_done() { done_ = true; }

private:
  std::optional<uint8_t> next_field_;
  bool done_;
};

struct BitStream : BaseBitStream {
  BitStream(std::istream &);

  std::pair<uint32_t, uint32_t> read_bits(uint32_t bit_cnt) override;

private:
  Generator<bool> gen_;
  Generator<bool>::Iter it_;
};

struct SubBitStream : BaseBitStream {
  SubBitStream(BaseBitStream &parent, uint32_t bit_limit);

  std::pair<uint32_t, uint32_t> read_bits(uint32_t bit_cnt) override;

  uint32_t limit() { return limit_; }

private:
  BaseBitStream *parent_;
  uint32_t limit_;
};

#endif