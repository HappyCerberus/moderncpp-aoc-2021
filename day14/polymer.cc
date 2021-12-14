#include "polymer.h"
#include <utility>

FrequencyCounter::FrequencyCounter(const std::string &input) : char_freq(26, 0), pair_freq{} {
  Pair pair = {'\0', '\0'};
  for (char c : input) {
    pair.first = std::exchange(pair.second, c);
    if (pair.first != '\0')
      pair_freq[pair]++;
    char_freq[c - 'A']++;
  }
}

void FrequencyCounter::tick(const InsertionRules &rules) {
  auto new_pair_freq = pair_freq;
  auto new_char_freq = char_freq;

  for (auto &pair : pair_freq) {
    if (!rules.contains(pair.first))
      continue;
    char c = rules.at(pair.first);
    new_pair_freq[pair.first] -= pair.second;
    new_char_freq[c - 'A'] += pair.second;

    Pair left{pair.first.first, c};
    Pair right{c, pair.first.second};
    new_pair_freq[left] += pair.second;
    new_pair_freq[right] += pair.second;
  }

  pair_freq = std::move(new_pair_freq);
  char_freq = std::move(new_char_freq);
}