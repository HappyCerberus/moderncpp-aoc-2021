#include "brackets.h"

#include <iostream>
#include <stack>
#include <unordered_map>

char first_unmatched(const std::string &input) {
  std::stack<char> memory;
  std::unordered_map<char, char> mapping = {{'(', ')'}, {'[', ']'}, {'<', '>'}, {'{', '}'}};
  for (char c : input) {
    if (mapping.contains(c))
      memory.push(c);
    else if (mapping[memory.top()] == c)
      memory.pop();
    else
      return c;
  }
  return '\0';
}

std::string autofix(const std::string &input) {
  std::stack<char> memory;
  std::unordered_map<char, char> mapping = {{'(', ')'}, {'[', ']'}, {'<', '>'}, {'{', '}'}};
  for (char c : input) {
    if (mapping.contains(c))
      memory.push(c);
    else if (mapping[memory.top()] == c)
      memory.pop();
  }
  std::string result = "";
  while (memory.size() != 0) {
    result += mapping[memory.top()];
    memory.pop();
  }
  return result;
}

uint64_t autofix_score(const std::string &input) {
  uint64_t result = 0;
  std::unordered_map<char, uint64_t> points_fix = {{')', 1}, {']', 2}, {'}', 3}, {'>', 4}};
  for (char c : input) {
    result *= 5;
    result += points_fix[c];
  }
  return result;
}