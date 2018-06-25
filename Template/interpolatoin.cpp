#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

using LL = long long;
const int MOD = (int)1e9 + 7;

struct Int {
  Int(LL x = 0) : x(x) {}
  Int& operator += (const Int& rhs) { if ((x += rhs.x) >= MOD) x -= MOD; return *this; }
  Int& operator -= (const Int& rhs) { if ((x += MOD - rhs.x) >= MOD) x -= MOD; return *this; }
  Int& operator *= (const Int& rhs) { (x *= rhs.x) %= MOD; return *this; }
  Int& operator /= (const Int& rhs) { (x *= rhs.inv().x) %= MOD; return *this; }
  Int operator + (const Int& rhs) const { return Int(*this) += rhs; }
  Int operator - (const Int& rhs) const { return Int(*this) -= rhs; }
  Int operator * (const Int& rhs) const { return Int(*this) *= rhs; }
  Int operator / (const Int& rhs) const { return Int(*this) /= rhs; }
  Int inv() const { return power(MOD - 2); }
  Int power(LL t) const {
    if (!t) return 1;
    Int ret = power(t / 2);
    ret *= ret;
    return (t & 1) ? ret * x : ret;
  }
  bool operator < (const Int& rhs) const { return x < rhs.x; }
  bool operator == (const Int& rhs) const { return x == rhs.x; }
  LL x;
};

Int lag(const std::vector<Int>&y, int D) {
  int d = y.size();
  Int ret = 0;
  for (int i = 0; i < d; ++ i) {
    Int a = 1, b = 1;
    for (int j = 0; j < d; ++ j)
      if (j != i)
        a *= (MOD + i - j), b *= (MOD + D - j);
    ret += y[i] / a * b;
  }
  return ret;
}
