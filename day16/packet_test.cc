#include "packet.h"

#include <gtest/gtest.h>

TEST(Packet, Literal) {
  std::stringstream input("D2FE28");
  BitStream bit_stream(input);
  Packet::Packet p;
  bit_stream >> p;
  EXPECT_EQ(p.version, 6);
  EXPECT_EQ(p.type_id, 4);
  EXPECT_TRUE(p.is_literal());
  EXPECT_EQ(p.literal_value(), 2021);
}

TEST(Packet, SubPacketsByBits) {
  std::stringstream input("38006F45291200");
  BitStream bit_stream(input);
  Packet::Packet p;
  bit_stream >> p;
  EXPECT_EQ(p.version, 1);
  EXPECT_EQ(p.type_id, 6);
  EXPECT_FALSE(p.is_literal());
  EXPECT_TRUE(p.has_subpackets());
  EXPECT_EQ(p.sub_packets().size(), 2);
  EXPECT_TRUE(p.sub_packets()[0].is_literal());
  EXPECT_TRUE(p.sub_packets()[1].is_literal());
  EXPECT_EQ(p.sub_packets()[0].literal_value(), 10);
  EXPECT_EQ(p.sub_packets()[1].literal_value(), 20);
}

TEST(Packet, SubPacketsByCount) {
  std::stringstream input("EE00D40C823060");
  BitStream bit_stream(input);
  Packet::Packet p;
  bit_stream >> p;
  EXPECT_EQ(p.version, 7);
  EXPECT_EQ(p.type_id, 3);
  EXPECT_FALSE(p.is_literal());
  EXPECT_TRUE(p.has_subpackets());
  EXPECT_EQ(p.sub_packets().size(), 3);
  EXPECT_TRUE(p.sub_packets()[0].is_literal());
  EXPECT_TRUE(p.sub_packets()[1].is_literal());
  EXPECT_TRUE(p.sub_packets()[2].is_literal());
  EXPECT_EQ(p.sub_packets()[0].literal_value(), 1);
  EXPECT_EQ(p.sub_packets()[1].literal_value(), 2);
  EXPECT_EQ(p.sub_packets()[2].literal_value(), 3);
}

TEST(Packet, VersionSums) {
  {
    std::stringstream input("8A004A801A8002F478");
    BitStream bit_stream(input);
    Packet::Packet p;
    bit_stream >> p;
    EXPECT_EQ(sum_versions(p), 16);
  }
  {
    std::stringstream input("620080001611562C8802118E34");
    BitStream bit_stream(input);
    Packet::Packet p;
    bit_stream >> p;
    EXPECT_EQ(sum_versions(p), 12);
  }
  {
    std::stringstream input("C0015000016115A2E0802F182340");
    BitStream bit_stream(input);
    Packet::Packet p;
    bit_stream >> p;
    EXPECT_EQ(sum_versions(p), 23);
  }
  {
    std::stringstream input("A0016C880162017C3686B18A3D4780");
    BitStream bit_stream(input);
    Packet::Packet p;
    bit_stream >> p;
    EXPECT_EQ(sum_versions(p), 31);
  }
}

TEST(Packet, Evaluation) {
  {
    std::stringstream input("C200B40A82");
    BitStream bit_stream(input);
    Packet::Packet p;
    bit_stream >> p;
    EXPECT_EQ(static_cast<uint64_t>(p), 3);
  }

  {
    std::stringstream input("04005AC33890");
    BitStream bit_stream(input);
    Packet::Packet p;
    bit_stream >> p;
    EXPECT_EQ(static_cast<uint64_t>(p), 54);
  }
  {
    std::stringstream input("04005AC33890");
    BitStream bit_stream(input);
    Packet::Packet p;
    bit_stream >> p;
    EXPECT_EQ(static_cast<uint64_t>(p), 54);
  }
  {
    std::stringstream input("880086C3E88112");
    BitStream bit_stream(input);
    Packet::Packet p;
    bit_stream >> p;
    EXPECT_EQ(static_cast<uint64_t>(p), 7);
  }
  {
    std::stringstream input("CE00C43D881120");
    BitStream bit_stream(input);
    Packet::Packet p;
    bit_stream >> p;
    EXPECT_EQ(static_cast<uint64_t>(p), 9);
  }
  {
    std::stringstream input("D8005AC2A8F0");
    BitStream bit_stream(input);
    Packet::Packet p;
    bit_stream >> p;
    EXPECT_EQ(static_cast<uint64_t>(p), 1);
  }
  {
    std::stringstream input("F600BC2D8F");
    BitStream bit_stream(input);
    Packet::Packet p;
    bit_stream >> p;
    EXPECT_EQ(static_cast<uint64_t>(p), 0);
  }
  {
    std::stringstream input("9C005AC2F8F0");
    BitStream bit_stream(input);
    Packet::Packet p;
    bit_stream >> p;
    EXPECT_EQ(static_cast<uint64_t>(p), 0);
  }
  {
    std::stringstream input("9C0141080250320F1802104A08");
    BitStream bit_stream(input);
    Packet::Packet p;
    bit_stream >> p;
    EXPECT_EQ(static_cast<uint64_t>(p), 1);
  }
}