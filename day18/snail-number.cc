#include "snail-number.h"
#include <istream>
#include <ostream>

std::istream &operator>>(std::istream &s, SnailNumber &number) {
  char c;
  if (!(s >> c))
    return s;
  if (c != '[')
    throw std::runtime_error("Expected left bracket.");
  number.left_ = std::make_unique<SnailNumber>();
  if (s.peek() == '[') {
    s >> *number.left_;
  } else {
    s >> number.left_->value_;
  }
  if (!(s >> c) || c != ',')
    throw std::runtime_error("Expected delimiter between left and right side of number.");
  number.right_ = std::make_unique<SnailNumber>();
  if (s.peek() == '[') {
    s >> *number.right_;
  } else {
    s >> number.right_->value_;
  }
  if (!(s >> c) || c != ']')
    throw std::runtime_error("Expeted right bracket.");
  return s;
}

std::ostream &operator<<(std::ostream &s, const SnailNumber &number) {
  if (number.is_terminal()) {
    s << number.value_;
    return s;
  }
  s << "[" << *number.left_ << "," << *number.right_ << "]";
  return s;
}

SnailNumber operator+(const SnailNumber &left, const SnailNumber &right) {
  SnailNumber result;
  result.left_ = std::make_unique<SnailNumber>(left);
  result.right_ = std::make_unique<SnailNumber>(right);
  do {
    while (result.explodes())
      ;
  } while (result.splits());
  return result;
}

SnailNumber::SnailNumber(const SnailNumber &other) : left_(nullptr), right_(nullptr), value_(other.value_) {
  if (other.is_terminal())
    return;
  left_ = std::make_unique<SnailNumber>(*other.left_);
  right_ = std::make_unique<SnailNumber>(*other.right_);
}

SnailNumber &SnailNumber::operator=(const SnailNumber &other) {
  if (this == &other)
    return *this;
  if (other.is_terminal()) {
    value_ = other.value_;
    left_ = nullptr;
    right_ = nullptr;
    return *this;
  }

  left_ = std::make_unique<SnailNumber>(*other.left_);
  right_ = std::make_unique<SnailNumber>(*other.right_);
  return *this;
}

SnailNumber::operator uint64_t() const {
  if (is_terminal())
    return value_;
  return 3 * static_cast<uint64_t>(*left_) + 2 * static_cast<uint64_t>(*right_);
}

bool SnailNumber::explodes() {
  std::optional<uint64_t> spill;
  std::optional<uint64_t *> last_value;
  return lr_search(0, last_value, spill) || spill.has_value();
}

bool SnailNumber::lr_search(uint32_t depth, std::optional<uint64_t *> &last_value, std::optional<uint64_t> &spill) {
  if (is_terminal()) {
    if (spill.has_value()) {
      value_ += spill.value();
      spill.reset();
      return true;
    }

    last_value = &value_;
    return false;
  }

  if (depth < 4 || spill.has_value() || !left_->is_terminal() || !right_->is_terminal()) {
    return left_->lr_search(depth + 1, last_value, spill) || right_->lr_search(depth + 1, last_value, spill);
  }

  // depth >= 4 && !spill.has_value() && left->is_terminal() && right->is_terminal()
  if (last_value.has_value()) {
    (*last_value.value()) += left_->value_;
  }
  spill = right_->value_;
  left_ = nullptr;
  right_ = nullptr;
  value_ = 0;
  return false;
}

bool SnailNumber::splits() {
  if (!is_terminal()) {
    if (left_->splits())
      return true;
    return right_->splits();
  }

  if (value_ < 10)
    return false;

  left_ = std::make_unique<SnailNumber>(value_ / 2);
  right_ = std::make_unique<SnailNumber>((value_ + 1) / 2);
  return true;
}