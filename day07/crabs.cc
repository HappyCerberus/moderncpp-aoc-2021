#include "crabs.h"
#include <algorithm>
#include <istream>
#include <numeric>

CrabSubmarines parse_input(std::istream &input) {
  CrabSubmarines result;
  int32_t v;
  char delim;
  while (input >> v) {
    if (input)
      input >> delim;
    if (delim != ',')
      throw std::runtime_error("Failed to parse input.");
    result.push_back(v);
  }
  return result;
}

int32_t minimum_fuel_to_aling(CrabSubmarines &subs) {
  std::ranges::sort(subs);
  auto mid = subs.begin() + (subs.size() / 2);

  auto left_it = mid--;
  auto right_it = mid++;
  int32_t best_left = std::accumulate(subs.begin(), subs.end(), 0, [target = *mid](auto sum, auto el) { return sum + std::abs(target - el); });
  int32_t best_right = best_left;

  while (left_it >= subs.begin()) {
    int32_t candidate = std::accumulate(subs.begin(), subs.end(), 0, [target = *left_it](auto sum, auto el) { return sum + std::abs(target - el); });
    if (candidate > best_left)
      break;
    best_left = candidate;
    left_it--;
  }
  while (right_it != subs.end()) {
    int32_t candidate = std::accumulate(subs.begin(), subs.end(), 0, [target = *right_it](auto sum, auto el) { return sum + std::abs(target - el); });
    if (candidate > best_right)
      break;
    best_right = candidate;
    right_it++;
  }
  return std::min(best_left, best_right);
}

int32_t minimum_fuel_to_properly_align(CrabSubmarines &subs, std::function<int32_t(int32_t, int32_t)> cost_fn) {
  std::ranges::sort(subs);
  auto mid = subs.begin() + (subs.size() / 2);

  int32_t lower = *mid - 1;
  int32_t higher = *mid + 1;
  int32_t best_left = std::accumulate(subs.begin(), subs.end(), 0, [target = *mid, &cost_fn](auto sum, auto el) { return sum + cost_fn(target, el); });
  int32_t best_right = best_left;

  while (lower >= 0) {
    int32_t candidate = std::accumulate(subs.begin(), subs.end(), 0, [target = lower, &cost_fn](auto sum, auto el) { return sum + cost_fn(target, el); });
    if (candidate > best_left)
      break;
    best_left = candidate;
    lower--;
  }
  while (higher <= subs.back()) {
    int32_t candidate = std::accumulate(subs.begin(), subs.end(), 0, [target = higher, &cost_fn](auto sum, auto el) { return sum + cost_fn(target, el); });
    if (candidate > best_right)
      break;
    best_right = candidate;
    higher++;
  }
  return std::min(best_left, best_right);
}

int32_t minimum_fuel_to_aling_v3(CrabSubmarines &subs) {
  std::ranges::sort(subs);
  auto mid = subs.begin() + (subs.size() / 2);

  auto left_it = mid;
  auto right_it = mid;
  int32_t best_left = std::accumulate(subs.begin(), subs.end(), 0, [target = *mid](auto sum, auto el) { return sum + std::abs(target - el); });
  int32_t best_right = best_left;

  while (left_it > subs.begin()) {
    int32_t curr = *left_it;
    left_it--;
    int32_t change = (curr - *left_it) * ((std::distance(left_it, subs.end() - 1) - (std::distance(subs.begin(), left_it) + 1)));
    if (change < 0)
      break;
    best_left += change;
  }
  while (right_it != subs.end()) {
    int32_t curr = *right_it;
    right_it++;
    if (right_it == subs.end())
      break;
    int32_t change = (*right_it - curr) * (std::distance(subs.begin(), left_it) - std::distance(right_it, subs.end()));
    if (change < 0)
      break;
    best_right += change;
  }
  return std::min(best_left, best_right);
}

#include <iostream>

int32_t minimum_fuel_to_aling_v4(CrabSubmarines &subs) {
  auto mid = subs.begin() + subs.size() / 2;
  std::ranges::nth_element(subs, mid);
  return std::accumulate(subs.begin(), subs.end(), 0, [target = *mid](auto sum, auto el) { return sum + std::abs(target - el); });
}