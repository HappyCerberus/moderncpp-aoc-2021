#include <chrono>
#include <fstream>
#include <iostream>

#include "bitstream.h"
#include "packet.h"

#include <algorithm>
#include <ranges>

int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cerr << "This program expects one parameter that is the input file to read.\n";
    return 1;
  }
  std::ifstream input(argv[1]);
  if (!input.is_open()) {
    std::cerr << "Failed to open file.\n";
    return 1;
  }

  BitStream stream(input);
  Packet::Packet packet;
  stream >> packet;
  std::cout << "Sum of all versions is " << sum_versions(packet) << " \n";
  std::cout << "Result of evalution is " << static_cast<uint64_t>(packet) << " \n";
}