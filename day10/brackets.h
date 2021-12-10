#ifndef BRACKETS_H_
#define BRACKETS_H_

#include <string>

char first_unmatched(const std::string &);
std::string autofix(const std::string &);
uint64_t autofix_score(const std::string &);

#endif