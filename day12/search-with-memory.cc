#include "search-with-memory.h"

#include <iostream>
#include <istream>
#include <unordered_set>

using Memory = std::unordered_set<std::string>;

Graph parse_graph(std::istream &input) {
  Graph result;
  std::string line;
  while (input >> line) {
    auto pos = line.find('-');
    if (pos == std::string::npos)
      throw std::runtime_error("Couldn't parse input, did not find '-' delimiter.");
    auto k = line.substr(0, pos);
    auto v = line.substr(pos + 1);
    result.insert({k, {}});
    if (k != "end" && v != "start")
      result[k].push_back(v);
    result.insert({v, {}});
    if (v != "end" && k != "start")
      result[v].push_back(k);
  }
  return result;
}

namespace {
uint64_t count_paths(const Graph &graph, std::string node, Memory &mem) {
  uint64_t cnt = 0;
  for (auto &next : graph.at(node)) {
    if (mem.contains(next))
      continue;
    if (next == "end") {
      cnt++;
      continue;
    }
    if (std::islower(next[0]))
      mem.insert(next);
    cnt += count_paths(graph, next, mem);
    if (std::islower(next[0]))
      mem.erase(next);
  }
  return cnt;
}

uint64_t count_complex_paths(const Graph &graph, std::string node, Memory &mem, std::string &golden_cave) {
  uint64_t cnt = 0;
  for (auto &next : graph.at(node)) {
    if (next == "end") {
      cnt++;
      continue;
    }
    if (std::islower(next[0])) {
      if (mem.contains(next)) {
        if (golden_cave != "")
          continue;
        golden_cave = next;
      } else {
        mem.insert(next);
      }
    }
    cnt += count_complex_paths(graph, next, mem, golden_cave);
    if (std::islower(next[0])) {
      if (golden_cave == next)
        golden_cave = "";
      else
        mem.erase(next);
    }
  }
  return cnt;
}
} // namespace

uint64_t count_paths(const Graph &graph) {
  Memory mem;
  return count_paths(graph, "start", mem);
}

uint64_t count_complex_paths(const Graph &graph) {
  Memory mem;
  std::string gc;
  return count_complex_paths(graph, "start", mem, gc);
}