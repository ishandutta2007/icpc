template<int MOD>
struct Integral {
  int v_ = 0;

  template<typename T> Integral(T v) : v_(norm(v)) {  // Implicit conversion is allowed.
    static_assert(std::is_integral<T>::value, "input should be an integral.");
  }
  Integral() = default;
  ~Integral() = default;

  template<typename T> T norm(T v) const {
    if constexpr(std::is_same<long long, T>::value) {
      v %= MOD;
      if (v < 0) v += MOD;
    } else {
      if (v >= MOD) v -= MOD;
      if (v < 0) v += MOD;
      if (v >= MOD || v < 0) {
        v %= MOD;
        if (v < 0) v += MOD;
      }
    }
    return v;
  }

  int val() const { return v_; }
  Integral& operator+=(const Integral& rhs) { v_ += rhs.val(); if (v_ >= MOD) v_ -= MOD; return *this; }
  Integral& operator-=(const Integral& rhs) { v_ += MOD - rhs.val(); if (v_ >= MOD) v_ -= MOD; return *this; }
  Integral& operator*=(const Integral& rhs) { v_ = v_ * 1LL * rhs.val() % MOD; return *this; }
  Integral& operator/=(const Integral& rhs) { v_ = v_ * 1LL * rhs.inv().val() % MOD; return *this; }
  Integral operator+(const Integral& rhs) const { Integral ret = *this; return ret += rhs; }
  Integral operator-(const Integral& rhs) const { Integral ret = *this; return ret -= rhs; }
  Integral operator*(const Integral& rhs) const { Integral ret = *this; return ret *= rhs; }
  Integral operator/(const Integral& rhs) const { Integral ret = *this; return ret /= rhs; }
  bool operator==(const Integral& rhs) const { return val() == rhs.val(); }
  bool operator!=(const Integral& rhs) const { return !(*this == rhs); }
  const Integral operator-() const { return Integral(-val()); }
  const Integral& operator++() { v_ += 1; if (v_ >= MOD) v_ -= MOD; return *this; }
  const Integral operator++(int) { Integral ret = *this; ++(*this); return ret; }
  const Integral& operator--() { v_ += MOD - 1; if (v_ >= MOD) v_ -= MOD; return *this; }
  const Integral operator--(int) { Integral ret = *this; --(*this); return ret; }

  Integral power(long long b) const {
    long long ret = 1 % MOD, a = v_;
    for ( ; b; b >>= 1, a = a * a % MOD) if (b & 1) ret = ret * a % MOD; return ret;
  }
  Integral inv() const { return power(MOD - 2); }
};

template<int MOD>
std::string to_string(const Integral<MOD>& v) {
  return std::string("{") + std::to_string(v.val()) + "}";
}

template<int MOD, bool kAllowBruteForce = false>
struct Binomial final {
  std::vector<Integral<MOD>> factor, inv_factor;

  explicit Binomial(int n = 0) : factor(n + 1), inv_factor(n + 1) {
    factor[0] = 1;
    for (int i = 1; i <= n; ++i) factor[i] = factor[i - 1] * i;
    inv_factor[n] = factor[n].inv();
    for (int i = n; i >= 1; --i) inv_factor[i - 1] = inv_factor[i] * i;
  }
  ~Binomial() = default;

  template<typename T>
  Integral<MOD> operator()(T a, T b) const {
    if (a < b || b < 0) return 0;
    if (a < factor.size()) return factor[a] * inv_factor[b] * inv_factor[a - b];
    if constexpr(!kAllowBruteForce) {
      throw std::out_of_range("Binomial");
    } else {
      b = std::min(b, a - b);
      Integral<MOD> ret = 1;
      for (T i = 1; i <= b; ++i) ret = ret * (a + 1 - i) / i;
      return ret;
    }
  }
};

template<int MOD>
struct PowerTable final : public std::vector<Integral<MOD>> {
  PowerTable(int n, const Integral<MOD>& g) {
    static_assert(sizeof(PowerTable) == sizeof(std::vector<Integral<MOD>>), "");
    this->resize(n + 1);
    this->at(0) = 1;
    this->at(1) = g;
    for (int i = 2; i < this->size(); ++i) this->at(i) = this->at(i - 1) * this->at(1);
  }
};

const int MOD = 998244353;
using Mint = Integral<MOD>;
using Binom = Binomial<MOD>;
using Power = PowerTable<MOD>;

// Binom binom(200000);
// Power pw2(200000, 2);

template<int MOD = 998244353, int kPrimRoot = 3>
void ntt(Integral<MOD> A[], int n, int inv) {
  // inv == 1: ntt, == -1: intt

  // MOD == a * b ^ k + 1, n <= b ^ k.
  // 998244353 == (7 * 17) * 2 ^ 23 + 1.
  // This code works only when b == 2.
  Integral<MOD> w = 1, d = Integral<MOD>(kPrimRoot).power((MOD - 1) / n), t;
  int i, j, c, s;
  if (inv == -1) {
    for (i = 1, j = n - 1; i < j; ++i, --j) std::swap(A[i], A[j]);
    for (t = Integral<MOD>(n).inv(), i = 0; i < n; ++i) A[i] = A[i] * t;
  }
  for (s = n >> 1; s; s >>= 1, w = 1, d = d * d) {
    for (c = 0; c < s; ++c, w = w * d) {
      for (i = c; i < n; i += s << 1) {
        A[i | s] = (A[i] - (t = A[i | s])) * w;
        A[i] += t;
      }
    }
  }
  for (i = 1; i < n; ++i) {
    for (j = 0, s = i, c = n >> 1; c; c >>= 1, s >>= 1) j = j << 1 | (s & 1);
    if (i < j) std::swap(A[i], A[j]);
  }
}

template<typename T>
struct Polynomial final : public std::vector<T> {
  Polynomial() = default;
  explicit Polynomial(int n) : std::vector<T>(n) {}
  Polynomial(int n, const T& val) : std::vector<T>(n, val) {}
  Polynomial(std::initializer_list<T> initializer_list) : std::vector<T>(std::move(initializer_list)) {}
  Polynomial(std::vector<T> vec) : std::vector<T>(std::move(vec)) {}
  int size() const { return std::vector<T>::size(); }
  T at(int pos) const { return pos >= 0 && pos < size() ? (*this)[pos] : T(0); }
  T& touch(int pos) { if (pos >= size()) std::vector<T>::resize(pos + 1, T(0)); return (*this)[pos]; }
  Polynomial mod(int n) const { return Polynomial(std::vector<T>(this->data(), this->data() + std::min(n, size()))); }
};

template<typename T>
void ntt(Polynomial<T>& poly, int n, int inv) {
  if (poly.size() < n) {
    poly.resize(n, 0);
  }
  return ntt(&poly[0], n, inv);
}

template<typename T>
void norm(Polynomial<T>& p) {
  while (p.size() > 1 && p.back() == T(0)) p.pop_back();
}

template<typename T>
Polynomial<T>& operator+=(Polynomial<T>& lhs, const Polynomial<T>& rhs) {
  lhs.resize(std::max(lhs.size(), rhs.size()), T(0));
  for (int i = 0; i < rhs.size(); ++i) lhs[i] += rhs[i];
  norm(lhs);
  return lhs;
}

template<typename T>
Polynomial<T> operator+(Polynomial<T> lhs, const Polynomial<T>& rhs) {
  return lhs += rhs;
}

template<typename T>
Polynomial<T>& operator-=(Polynomial<T>& lhs, const Polynomial<T>& rhs) {
  lhs.resize(std::max(lhs.size(), rhs.size()), T(0));
  for (int i = 0; i < rhs.size(); ++i) lhs[i] -= rhs[i];
  norm(lhs);
  return lhs;
}

template<typename T>
Polynomial<T> operator-(Polynomial<T> lhs, const Polynomial<T>& rhs) {
  return lhs -= rhs;
}

template<typename T>
Polynomial<T> mod_len(Polynomial<T> poly, int len) {
  // poly % x^len
  if (poly.size() > len) {
    poly.resize(len);
  }
  norm(poly);
  return poly;
}

template<typename T>
Polynomial<T> enforce_len(Polynomial<T> poly, int len) {
  poly.resize(len, 0);
  return poly;
}

int binary_upper_bound(int w) {
  if (w <= 0) return 1;
  const int highbit = 31 - __builtin_clz(w);
  return (1 << (highbit + 1));
}

template<typename T>
int get_ntt_len(const Polynomial<T>& lhs, const Polynomial<T>& rhs) {
  return binary_upper_bound((int)lhs.size() + (int)rhs.size() - 2);
}

template<typename T>
Polynomial<T> operator*(Polynomial<T> lhs, Polynomial<T> rhs) {
  CHECK(lhs.size() + rhs.size() > 0);
  const int L = get_ntt_len(lhs, rhs);
  lhs.resize(L, 0);
  rhs.resize(L, 0);
  ntt(lhs, L, 1);
  ntt(rhs, L, 1);
  for (int i = 0; i < L; ++i) {
    lhs[i] *= rhs[i];
  }
  ntt(lhs, L, -1);
  norm(lhs);
  return lhs;
}

template<typename T>
Polynomial<T> operator*(T a, Polynomial<T> p) {
  for (int i = 0; i < p.size(); ++i) p[i] *= a;
  norm(p);
  return p;
}

template<typename T>
Polynomial<T> mod_inv(Polynomial<T> poly, int len = 0) {
  // https://www.luogu.com.cn/problem/P4238
  CHECK(poly.size() >= 1 && poly[0] != 0);
  if (len == 0) len = poly.size();
  if (len > poly.size()) poly.resize(len);
  // poly * inv(poly) % (x^len) == 1

  const int L = binary_upper_bound(len - 1);
  poly.resize(L, 0);
  Polynomial<T> w(L << 1), r(L << 1), saved(L << 1);
  w[0] = poly[0].inv();
  for (int len = 2; len <= L; len <<= 1) {
    std::copy(w.begin(), w.begin() + (len >> 1), r.begin());
    std::copy(poly.begin(), poly.begin() + len, saved.begin());
    ntt(saved, len, 1);
    ntt(r, len, 1);
    for (int i = 0; i < len; ++i) r[i] *= saved[i];
    ntt(r, len, -1);
    for (int i = 0; i < (len >> 1); ++i) r[i] = 0;
    std::copy(w.begin(), w.begin() + len, saved.begin());
    ntt(saved, len, 1);
    ntt(r, len, 1);
    for (int i = 0; i < len; ++i) r[i] *= saved[i];
    ntt(r, len, -1);
    for (int i = (len >> 1); i < len; ++i) w[i] = w[i] + w[i] - r[i];
  }
  return mod_len(w, len);
}

template<typename T>
Polynomial<T> div(Polynomial<T> lhs, Polynomial<T> rhs) {  // Division with remainder.
  norm(lhs);
  norm(rhs);
  if (lhs.size() < rhs.size()) return Polynomial<T>(1, T(0));
  std::reverse(lhs.begin(), lhs.end());
  std::reverse(rhs.begin(), rhs.end());
  int len = (int)lhs.size() - 1 - (int)rhs.size() + 1 + 1;
  Polynomial<T> Q = enforce_len(lhs * mod_inv(rhs, len), len);
  std::reverse(Q.begin(), Q.end());
  norm(Q);
  return Q;
}

template<typename T>
Polynomial<T> operator%(Polynomial<T> lhs, Polynomial<T> rhs) {
  Polynomial<T> Q = div(lhs, rhs);
  return lhs - Q * rhs;
}

template<typename T>
T eval(const Polynomial<T>& poly, T a) {  // Returns Poly(a).
  T ret = 0;
  T w = 1;
  for (int i = 0; i < poly.size(); ++i) {
    ret += w * poly[i];
    w *= a;
  }
  return ret;
  // NOTE: It equals to (poly % Polynomial<T>{-a, 1}).at(0).
}

template<typename T>
Polynomial<T> derivate(Polynomial<T> poly) {
  if (poly.size() <= 1) {
    return Polynomial<T>(1, 0);
  }
  for (int i = 1; i < poly.size(); ++i) {
    poly[i - 1] = poly[i] * i;
  }
  poly.pop_back();
  norm(poly);
  return poly;
}

template<typename T>
Polynomial<T> integrate(Polynomial<T> poly) {
  if (poly.size() == 0) {
    return poly;
  }
  poly.emplace_back(0);
  for (int i = (int)poly.size() - 1; i > 0; --i) {
    poly[i] = poly[i - 1] / i;
  }
  poly[0] = 0;
  norm(poly);
  return poly;
}

template<typename T>
Polynomial<T> mod_sqrt(Polynomial<T> poly, int len = 0) {
  // https://www.luogu.com.cn/problem/P5205
  CHECK(poly.size() >= 1 && poly[0] == 1);  // Or quadratic residue without this constraint.
  if (len > poly.size()) poly.resize(len);
  if (poly.size() == 1) {
    return poly;
  }
  if (len == 0) len = poly.size();
  const int L = binary_upper_bound(len - 1);
  poly.resize(L, 0);
  Polynomial<T> buffer(1, 1), buffer1;
  for (int len = 2; len <= L; len <<= 1) {
    buffer1 = mod_inv(T(2) * buffer, len);
    ntt(buffer, len, 1);
    for (int i = 0; i < len; ++i) buffer[i] *= buffer[i];
    ntt(buffer, len, -1);
    for (int i = 0; i < len; ++i) buffer[i] += poly[i];
    buffer = enforce_len(buffer * buffer1, len);
  }
  return mod_len(buffer, len);
}

template<typename T>
Polynomial<T> mod_ln(Polynomial<T> poly, int len = 0) {
  // https://www.luogu.com.cn/problem/P4725
  if (len == 0) len = poly.size();
  if (len > poly.size()) poly.resize(len);
  return mod_len(integrate(derivate(poly) * mod_inv(poly, len)), len);
}

template<typename T>
Polynomial<T> mod_exp(Polynomial<T> poly, int len = 0) {
  // https://www.luogu.com.cn/problem/P4726
  if (len == 0) len = poly.size();
  if (len > poly.size()) poly.resize(len);
  CHECK(poly.size() == 0 || poly[0] == 0);
  const int L = binary_upper_bound(len - 1);
  poly.resize(L, 0);
  Polynomial<T> p(1, 1);
  for (int len = 2; len <= L; len <<= 1) {
    Polynomial<T> q = p;
    p = enforce_len(mod_ln(p, len), len);
    for (int i = 0; i < len; ++i) p[i] = poly[i] - p[i];
    ++p[0];
    p = mod_len(p * q, len);
  }
  return mod_len(p, len);
}

template<typename T>
Polynomial<T> conditioned_mod_power(Polynomial<T> poly, T k, int len = 0) {
  // https://www.luogu.com.cn/problem/P5245
  CHECK(poly.size() >= 1 && poly[0] != T(0));  // In case poly[0] == T(0), find another way.
  if (len == 0) len = poly.size();
  T constant = poly[0];
  if (constant != T(1)) {
    T inv_constant = T(1) / constant;
    for (int i = 0; i < poly.size(); ++i) {
      poly[i] *= inv_constant;
    }
  }
  Polynomial<T> ret = mod_exp(k * mod_ln(poly, len), len);
  if (constant != T(1)) {
    constant = constant.power(k.val());
    for (int i = 0; i < ret.size(); ++i) {
      ret[i] *= constant;
    }
  }
  return ret;
}

template<typename T>
Polynomial<T> mod_euler_transform(const Polynomial<T>& poly, int len = 0) {
  // https://www.luogu.com.cn/problem/P4389
  if (poly.size() < 2) return Polynomial<T>{};
  CHECK(poly[0] == T(0));
  if (len == 0) len = poly.size();
  Polynomial<T> P(len);
  std::vector<T> inv(len);
  for (int i = 1; i < len; ++i) {
    inv[i] = Mint(i).inv();
  }
  for (int i = 1; i < poly.size(); ++i) if (poly[i].val()) {
    for (int j = 1; i * j < len; ++j) {
      P[i * j] += poly[i] * inv[j];
    }
  }
  return mod_exp(P, len);
}

template<typename T>
T lagrange_inversion(Polynomial<T> poly, int n) {  // WARNING: Has not been instantiated
  if (poly.empty()) return T(0);
  CHECK(poly[0] == T(0));
  CHECK(poly.size() > 1);
  CHECK(poly[1] != T(0));
  CHECK(n > 0);
  poly.erase(poly.begin());
  return enforce_len(conditioned_mod_power(poly, n, n), n)[n - 1] / T(n);
}

using Poly = Polynomial<Integral<MOD>>;

