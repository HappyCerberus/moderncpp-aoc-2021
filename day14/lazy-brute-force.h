#ifndef LAZY_BRUTE_FORCE_H_
#define LAZY_BRUTE_FORCE_H_

#include "generator.h"
#include "parsing.h"

Generator<char> polymer_expander(std::string);
Generator<char> polymer_expander(InsertionRules &, Generator<char>);

#endif