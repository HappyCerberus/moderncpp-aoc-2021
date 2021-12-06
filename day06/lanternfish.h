#include <cstdint>
#include <deque>
#include <string>

using Population = std::deque<uint64_t>;

void init_population(Population &pop, const std::string &input);
void simulate_day(Population &population);
uint64_t total_pop_count(Population &population);