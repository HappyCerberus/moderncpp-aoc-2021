#include "packet.h"

#include <algorithm>
#include <iostream>
#include <numeric>

namespace Packet {

BaseBitStream &operator>>(BaseBitStream &s, Literal &lit) {
  uint64_t value = 0;
  while (true) {
    uint32_t data = 0;
    if (!(s >> field_width(5) >> data))
      throw std::runtime_error("Failed to read literal chunk.");
    value = (value << 4) | (data & UINT32_C(0b1111));
    if (!(data & UINT32_C(0b10000)))
      break;
  }
  lit.data = value;
  return s;
}

BaseBitStream &operator>>(BaseBitStream &s, LengthOrCount &cnt) {
  if (!(s >> field_width(1) >> cnt.is_count))
    return s;

  if (cnt.is_count) {
    s >> field_width(11) >> cnt.size;
  } else {
    s >> field_width(15) >> cnt.size;
  }
  return s;
}

BaseBitStream &operator>>(BaseBitStream &s, Packet &p) {
  if (!(s >> field_width(3) >> p.version >> field_width(3) >> p.type_id)) {
    return s;
  }

  if (p.is_literal()) {
    Literal lit;
    s >> lit;
    p.data = lit;
  } else {
    Packet::SubPackets packets;
    s >> packets.size;
    if (packets.size.is_count) {
      for (uint32_t i = 0; i < packets.size.size; i++) {
        Packet subp;
        s >> subp;
        packets.packets.push_back(subp);
      }
    } else {
      SubBitStream stream(s, packets.size.size);
      Packet subp;
      while (stream >> subp)
        packets.packets.push_back(subp);
    }
    p.data = packets;
  }
  return s;
}

uint32_t sum_versions(const Packet &p) {
  if (std::holds_alternative<Literal>(p.data)) {
    return p.version;
  } else {
    uint32_t sum = p.version;
    for (auto &subp : p.sub_packets()) {
      sum += sum_versions(subp);
    }
    return sum;
  }
}

Packet::operator uint64_t() const {
  switch (type_id) {
  case 0:
    return std::accumulate(sub_packets().begin(), sub_packets().end(), UINT64_C(0), std::plus<>());
  case 1:
    return std::accumulate(sub_packets().begin(), sub_packets().end(), UINT64_C(1), std::multiplies<>());
  case 2:
    return *std::ranges::min_element(sub_packets());
  case 3:
    return *std::ranges::max_element(sub_packets());
  case 4:
    return literal_value();
  case 5:
    return static_cast<uint64_t>(sub_packets()[0]) > static_cast<uint64_t>(sub_packets()[1]);
  case 6:
    return static_cast<uint64_t>(sub_packets()[0]) < static_cast<uint64_t>(sub_packets()[1]);
  case 7:
    return static_cast<uint64_t>(sub_packets()[0]) == static_cast<uint64_t>(sub_packets()[1]);
  }
  return 0;
}

bool Packet::is_literal() const { return type_id == 4; }
bool Packet::has_subpackets() const { return type_id != 4 && std::holds_alternative<SubPackets>(data); }
uint64_t Packet::literal_value() const { return std::get<Literal>(data).data; }
const std::vector<Packet> &Packet::sub_packets() const { return std::get<SubPackets>(data).packets; }

} // namespace Packet