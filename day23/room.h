#ifndef ROOM_H_
#define ROOM_H_

#include <initializer_list>
#include <unordered_map>
#include <vector>

using size_t = std::size_t;

const inline std::unordered_map<char, size_t> COST = {{'A', 1}, {'B', 10}, {'C', 100}, {'D', 1000}};

struct Room {
  Room(char who, std::initializer_list<char> data);

  bool is_finished() const;
  bool can_accept() const;
  bool has_visitors() const;
  char top() const;
  size_t pop();
  size_t push(char who);
  char at(size_t index) const { return data_[index]; }

private:
  char owner_;
  std::vector<char> data_;
  size_t size_;
  size_t fixed_;
};

#endif