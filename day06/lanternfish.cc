#include "lanternfish.h"
#include <algorithm>
#include <numeric>
#include <sstream>

void init_population(Population &pop, const std::string &input) {
  pop.resize(9);
  std::ranges::fill(pop, 0);

  std::stringstream s(input);
  uint32_t timer;
  char delimiter;

  while (s >> timer) {
    pop[timer]++;
    s >> delimiter;
    if (s && delimiter != ',')
      throw std::runtime_error("Malformed intput.");
  }
}

uint64_t total_pop_count(Population &population) { return std::accumulate(population.begin(), population.end(), UINT64_C(0), std::plus<uint64_t>()); }

void simulate_day(Population &population) {
  uint64_t reproducing = population.front();
  population.pop_front();
  population.push_back(0);
  if (std::numeric_limits<uint64_t>::max() - reproducing < population[6])
    throw std::overflow_error("Overflow when reproducing.");
  population[6] += reproducing;
  population[8] = reproducing;
}