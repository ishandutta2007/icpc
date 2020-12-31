template<int MOD>
struct Integral {
  int v_ = 0;

  Integral() {}
  template<typename T> Integral(T v) : v_(norm(v)) {  // Implicit conversion is allowed.
    static_assert(std::is_integral<T>::value, "input should be an integral.");
  }
  ~Integral() = default;

  template<typename T> T norm(T v) const {
    if (v >= MOD) v -= MOD;
    if (v < 0) v += MOD;
    if (v >= MOD || v < 0) v = (v % MOD + MOD) % MOD;
    return v;
  }

  int val() const { return v_; }

  Integral power(long long b) const {
    long long ret = 1 % MOD, a = v_;
    for ( ; b; b >>= 1, a = a * a % MOD) if (b & 1) ret = ret * a % MOD; return ret;
  }
  Integral inv() const { return power(MOD - 2); }
};

// +
template<int MOD> inline Integral<MOD> operator + (const Integral<MOD>& lhs, const Integral<MOD>& rhs) {
  return Integral<MOD>(lhs.val() + rhs.val());
}
template<int MOD> inline Integral<MOD>& operator += (Integral<MOD>& lhs, const Integral<MOD> & rhs) {
  return lhs = lhs + rhs;
}

// -
template<int MOD> inline Integral<MOD> operator - (const Integral<MOD>& lhs, const Integral<MOD>& rhs) {
  return Integral<MOD>(lhs.val() - rhs.val());
}
template<int MOD> inline Integral<MOD>& operator -= (Integral<MOD>& lhs, const Integral<MOD>& rhs) {
  return lhs = lhs - rhs;
}

// *
template<int MOD> inline Integral<MOD> operator * (const Integral<MOD>& lhs, const Integral<MOD>& rhs) {
  return Integral<MOD>(lhs.val() * 1LL * rhs.val());
}
template<int MOD> inline Integral<MOD>& operator *= (Integral<MOD>& lhs, const Integral<MOD>& rhs) {
  return lhs = lhs * rhs;
}

// /
template<int MOD> inline Integral<MOD> operator / (const Integral<MOD>& lhs, const Integral<MOD>& rhs) {
  return lhs * rhs.inv();
}
template<int MOD> inline Integral<MOD>& operator /= (Integral<MOD>& lhs, const Integral<MOD>& rhs) {
  return lhs = lhs / rhs;
}

// ==
template<int MOD> inline bool operator == (const Integral<MOD>& lhs, const Integral<MOD>& rhs) {
  return lhs.val() == rhs.val();
}
template<int MOD> inline bool operator != (const Integral<MOD>& lhs, const Integral<MOD>& rhs) {
  return !(lhs == rhs);
}

// Uinary
template<int MOD> inline Integral<MOD> operator - (const Integral<MOD>& v) { return Integral<MOD>(-v.val()); }
template<int MOD> inline Integral<MOD> operator ++ (Integral<MOD>& v) { return v = Integral<MOD>(v.val() + 1); }
template<int MOD> inline Integral<MOD> operator ++ (Integral<MOD>& v, int) { Integral<MOD> ret = v; ++v; return ret; }
template<int MOD> inline Integral<MOD> operator -- (Integral<MOD>& v) { return v = Integral<MOD>(v.val() - 1); }
template<int MOD> inline Integral<MOD> operator -- (Integral<MOD>& v, int) { Integral<MOD> ret = v; --v; return ret; }

template<int MOD>
std::string to_string(const Integral<MOD>& v) {
  return std::string("Integral{v=") + std::to_string(v.val()) + "}";
}

template<int MOD>
struct Binomial {
  std::vector<Integral<MOD>> factor, inv_factor;

  void init(int n) {
    factor.resize(n + 1);
    inv_factor.resize(n + 1);
    factor[0] = 1;
    for (int i = 1; i <= n; ++i) factor[i] = factor[i - 1] * i;
    inv_factor[n] = factor[n].inv();
    for (int i = n; i >= 1; --i) inv_factor[i - 1] = inv_factor[i] * i;
  }

  Integral<MOD> operator () (int a, int b) const {
    if (a < b || b < 0) return 0;
    if (a < factor.size()) return factor[a] * inv_factor[b] * inv_factor[a - b];
    b = std::min(b, a - b);
    Integral<MOD> ret = 1;
    for (int i = 1; i <= b; ++i) ret = ret * (a + 1 - i) / i;
    return ret;
  }
};

