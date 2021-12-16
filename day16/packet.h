#ifndef PACKET_H_
#define PACKET_H_

#include "bitstream.h"
#include <variant>
#include <vector>

namespace Packet {

struct Literal {
  uint64_t data;
  friend BaseBitStream &operator>>(BaseBitStream &, Literal &);
};

struct LengthOrCount {
  bool is_count;
  uint32_t size;

  friend BaseBitStream &operator>>(BaseBitStream &, LengthOrCount &);
};

struct Packet {
  uint32_t version;
  uint32_t type_id;
  struct SubPackets {
    LengthOrCount size;
    std::vector<Packet> packets;
  };
  std::variant<Literal, SubPackets> data;

  bool is_literal() const;
  bool has_subpackets() const;
  uint64_t literal_value() const;
  const std::vector<Packet> &sub_packets() const;

  friend BaseBitStream &operator>>(BaseBitStream &, Packet &);

  operator uint64_t() const;
};

uint32_t sum_versions(const Packet &p);

} // namespace Packet

#endif