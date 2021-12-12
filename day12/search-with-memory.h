#ifndef SEARCH_WITH_MEMORY_H_
#define SEARCH_WITH_MEMORY_H_

#include <iosfwd>
#include <string>
#include <unordered_map>
#include <vector>

using Graph = std::unordered_map<std::string, std::vector<std::string>>;

Graph parse_graph(std::istream &);
uint64_t count_paths(const Graph &);
uint64_t count_complex_paths(const Graph &);

#endif