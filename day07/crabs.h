#ifndef CRABS_H_
#define CRABS_H_

#include <cstdint>
#include <functional>
#include <iosfwd>
#include <vector>

using CrabSubmarines = std::vector<int32_t>;

CrabSubmarines parse_input(std::istream &);
int32_t minimum_fuel_to_aling(CrabSubmarines &subs);
int32_t minimum_fuel_to_properly_align(CrabSubmarines &subs, std::function<int32_t(int32_t, int32_t)>);
int32_t minimum_fuel_to_aling_v3(CrabSubmarines &subs);
int32_t minimum_fuel_to_aling_v4(CrabSubmarines &subs);

#endif