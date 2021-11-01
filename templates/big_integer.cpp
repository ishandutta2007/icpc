#include <bits/stdc++.h>
#ifdef ALGO
#include "el_psy_congroo.hpp"
#else
#define DUMP(...)
#define CHECK(...)
#endif

namespace {

template<typename BaseType = int8_t, BaseType BASE = 10>
struct BigInteger {
 public:
  static_assert(std::numeric_limits<BaseType>::max() / BASE >= BASE, "BASE^2 should be in range");
  BigInteger() : digits_(1, 0) {}
  template<typename T> BigInteger(T x) {  // Implicit conversion is allowed.
    static_assert(std::is_integral<T>::value, "T should be an integral type.");
    if (x < 0) {
      signbit_ = -1;
      x = -x;
    }
    for (; x; x /= BASE) digits_.emplace_back(x % BASE);
    if (digits_.empty()) digits_.emplace_back(0);
  }
  BigInteger operator-() const { if (is_zero()) return *this; BigInteger ret = *this; ret.signbit_ *= -1; return ret; }
  BigInteger& operator+=(const BigInteger& other) {
    std::vector<BaseType> tmp(std::max(digits_.size(), other.digits().size()) + 1);
    for (int i = 0; i < digits_.size(); ++i) tmp[i] += signed_digit(i);
    for (int i = 0; i < other.digits().size(); ++i) tmp[i] += other.signed_digit(i);
    BaseType carry = 0;
    for (int i = 0; i < tmp.size(); ++i) {
      tmp[i] += carry;
      if (tmp[i] <= -BASE) carry = -1, tmp[i] += BASE;
      else if (tmp[i] >= BASE) carry = 1, tmp[i] -= BASE;
      else carry = 0;
    }
    norm(tmp);
    if (tmp.back() < 0) {
      signbit_ = -1;
      for (int i = 0; i < tmp.size(); ++i) tmp[i] = -tmp[i];
    } else {
      signbit_ = 1;
    }
    for (int i = 0; i < tmp.size(); ++i) {
      tmp[i] += carry;
      if (tmp[i] < 0) {
        tmp[i] += BASE;
        carry = -1;
      } else {
        carry = 0;
      }
    }
    norm(tmp);
    digits_.swap(tmp);
    return *this;
  }
  BigInteger operator+(const BigInteger& other) const { BigInteger ret = *this; ret += other; return ret; }
  BigInteger& operator-=(const BigInteger& other) { return (*this) += (-other); }
  BigInteger operator-(const BigInteger& other) const { BigInteger ret = *this; ret -= other; return ret; }
  BigInteger& operator*=(const BigInteger& other) {
    // TODO
    throw;
  }
  BigInteger operator*(const BigInteger& other) const { BigInteger ret = *this; ret *= other; return ret; }
  BigInteger& operator/=(const BigInteger& other) {
    // TODO
    throw;
  }
  BigInteger operator/(const BigInteger& other) const { BigInteger ret = *this; ret /= other; return ret; }
  BaseType signbit() const { return signbit_; }
  const std::vector<BaseType>& digits() const { return digits_; }
  bool is_zero() const { return digits_.size() == 1 && digits_[0] == 0; }
 private:
  BaseType signed_digit(int pos) const { return signbit_ * digits_[pos]; }
  void norm() { norm(digits_); if (is_zero()) signbit_ = 1; }
  void norm(std::vector<BaseType>& digits) { while (digits.size() > 1 && digits.back() == 0) digits.pop_back(); }
  BaseType signbit_ = 1;
  std::vector<BaseType> digits_;
};

template<typename BaseType = int8_t, BaseType BASE = 10>
std::string to_string(const BigInteger<BaseType, BASE>& integer, const std::string& seperator = "_") {
  std::string ret;
  if (integer.signbit() == -1) ret += std::string("-") + seperator;
  for (int i = (int)integer.digits().size() - 1; i >= 0; --i) {
    ret += std::to_string(integer.digits()[i]);
    if (i > 0) ret += seperator;
  }
  return ret;
}

struct Solver {

  void solve(int ca, std::istream& reader) {
    BigInteger w(15);
    DUMP((-w).signbit());
    DUMP(w);
    DUMP(-w);
    DUMP(-BigInteger(0));
    DUMP(BigInteger(123456) + BigInteger(-1000000));
    std::cout << to_string(BigInteger(123456) + BigInteger(-1000000), "") << std::endl;
  }
};

}  // namespace

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::istream& reader = std::cin;

  int cas = 1;
  // reader >> cas;
  for (int ca = 1; ca <= cas; ++ca) {
    auto solver = std::make_unique<Solver>();
    solver->solve(ca, reader);
  }
}

