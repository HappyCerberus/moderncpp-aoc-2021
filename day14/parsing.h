#ifndef PARSING_H_
#define PARSING_H_

#include "pair.h"
#include <iosfwd>
#include <string>
#include <unordered_map>

using InsertionRules = std::unordered_map<Pair, char>;

std::pair<std::string, InsertionRules> parse_rules(std::istream &);

#endif