#ifndef POLYMER_H_
#define POLYMER_H_

#include "pair.h"
#include "parsing.h"
#include <string>
#include <unordered_map>
#include <vector>

struct FrequencyCounter {
  FrequencyCounter(const std::string &);
  void tick(const InsertionRules &);
  std::vector<uint64_t> char_freq;
  std::unordered_map<Pair, uint64_t> pair_freq;
};

#endif