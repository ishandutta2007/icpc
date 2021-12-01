// An floating-point type wrapper designed to be compatible with other code snippets in this repo.
template<typename T>
struct FloatingPoint {
  T v_ = 0.0;

  FloatingPoint(T v) : v_(v) {  // Implicit conversion is allowed.
    static_assert(std::is_floating_point<T>::value, "input should be an floating point.");
  }
  FloatingPoint() = default;
  ~FloatingPoint() = default;

  static int cmp(T x) { static constexpr T eps = 1e-8; return x < -eps ? -1 : x > eps; }

  T val() const { return v_; }
  FloatingPoint& operator+=(const FloatingPoint& rhs) { v_ += rhs.val(); return *this; }
  FloatingPoint& operator-=(const FloatingPoint& rhs) { v_ -= rhs.val(); return *this; }
  FloatingPoint& operator*=(const FloatingPoint& rhs) { v_ *= rhs.val(); return *this; }
  FloatingPoint& operator/=(const FloatingPoint& rhs) { v_ /= rhs.val(); return *this; }
  FloatingPoint operator+(const FloatingPoint& rhs) const { FloatingPoint ret = *this; return ret += rhs; }
  FloatingPoint operator-(const FloatingPoint& rhs) const { FloatingPoint ret = *this; return ret -= rhs; }
  FloatingPoint operator*(const FloatingPoint& rhs) const { FloatingPoint ret = *this; return ret *= rhs; }
  FloatingPoint operator/(const FloatingPoint& rhs) const { FloatingPoint ret = *this; return ret /= rhs; }
  bool operator==(const FloatingPoint& rhs) const { return cmp(val() - rhs.val()) == 0; }
  bool operator!=(const FloatingPoint& rhs) const { return !(*this == rhs); }
  const FloatingPoint operator-() const { return FloatingPoint(-val()); }
  const FloatingPoint& operator++() { v_ += 1.0; return *this; }
  const FloatingPoint operator++(int) { FloatingPoint ret = *this; ++(*this); return ret; }
  const FloatingPoint& operator--() { v_ -= 1.0; return *this; }
  const FloatingPoint operator--(int) { FloatingPoint ret = *this; --(*this); return ret; }

  FloatingPoint power(T b) const { return FloatingPoint(std::pow(val(), b)); }
  FloatingPoint inv() const { return FloatingPoint(1.0 / val()); }
};

template<typename T>
std::string to_string(const FloatingPoint<T>& v) {
  return std::string("{") + std::to_string(v.val()) + "}";
}

using Float = FloatingPoint<float>;
using Double = FloatingPoint<double>;
using LongDouble = FloatingPoint<long double>;

