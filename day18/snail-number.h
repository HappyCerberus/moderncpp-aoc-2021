#ifndef NUMBER_H_
#define NUMBER_H_

#include <cstdint>
#include <iosfwd>
#include <memory>
#include <optional>

struct SnailNumber {
  SnailNumber() = default;
  SnailNumber(SnailNumber &&) = default;
  SnailNumber &operator=(SnailNumber &&) = default;

  SnailNumber(uint64_t value) : left_(nullptr), right_(nullptr), value_(value) {}
  SnailNumber(const SnailNumber &);
  SnailNumber &operator=(const SnailNumber &);

  explicit operator uint64_t() const;

private:
  std::unique_ptr<SnailNumber> left_;
  std::unique_ptr<SnailNumber> right_;
  uint64_t value_;

  bool is_terminal() const { return left_ == nullptr && right_ == nullptr; }
  bool explodes();
  bool lr_search(uint32_t depth, std::optional<uint64_t *> &last_value, std::optional<uint64_t> &spill);
  bool splits();

  friend std::istream &operator>>(std::istream &, SnailNumber &);
  friend std::ostream &operator<<(std::ostream &, const SnailNumber &);
  friend SnailNumber operator+(const SnailNumber &left, const SnailNumber &right);
  // tests
  friend bool one_explode(SnailNumber &);
  friend bool one_split(SnailNumber &);
};

#endif