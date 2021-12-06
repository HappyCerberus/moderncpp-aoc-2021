#include <algorithm>
#include <array>
#include <cstdint>
#include <iostream>
#include <numeric>

constexpr std::array<uint64_t, 9> step(std::array<uint64_t, 9> pop) {
  std::ranges::rotate(pop, pop.begin() + 1);
  pop[6] += pop[8];
  return pop;
}

template <uint32_t generation_cnt> constexpr std::array<uint64_t, 9> loop(std::array<uint64_t, 9> init) {
  for (uint32_t i = 0; i < generation_cnt; i++) {
    init = step(init);
  }
  return init;
}

constexpr uint64_t count_pop(std::array<uint64_t, 9> pop) { return std::accumulate(pop.begin(), pop.end(), UINT64_C(0), std::plus<>()); }

template <uint64_t Input> void printer() { std::cout << "Compile time result " << Input << "\n"; }

int main() {
  constexpr const std::array<uint64_t, 9> pop{0, 1, 1, 2, 1, 0, 0, 0, 0};
  constexpr const auto pop18 = loop<18>(pop);
  constexpr const auto pop80 = loop<80>(pop);
  printer<count_pop(pop18)>();
  printer<count_pop(pop80)>();
}