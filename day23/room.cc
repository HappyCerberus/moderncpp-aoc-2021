#include "room.h"

#include <algorithm>
#include <stdexcept>

Room::Room(char who, std::initializer_list<char> data) : owner_(who), data_(data), size_(data.size()), fixed_(0) {
  size_ -= std::ranges::count(data_, '.');
  auto it = std::ranges::find_if_not(data_, [who](char c) { return c == who; });
  fixed_ = it - data_.begin();
}

bool Room::is_finished() const { return fixed_ == data_.size(); }
bool Room::can_accept() const { return fixed_ == size_ && size_ != data_.size(); }
bool Room::has_visitors() const { return fixed_ != data_.size() && fixed_ != size_ && size_ != 0; }
char Room::top() const {
  if (size_ == 0)
    throw std::runtime_error("Room is empty.");
  return data_[size_ - 1];
}

size_t Room::pop() {
  size_t cost = (data_.size() - size_ + 1) * COST.at(data_[size_ - 1]);
  data_[size_ - 1] = '.';
  size_--;
  return cost;
}

size_t Room::push(char who) {
  if (!can_accept())
    throw std::runtime_error("Room can't accept data.");
  if (who != owner_)
    throw std::runtime_error("Tried to push the wrong type.");
  size_t cost = (data_.size() - size_) * COST.at(who);
  data_[size_] = who;
  size_++;
  fixed_++;
  return cost;
}
