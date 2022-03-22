template<int MOD> struct PrimitiveRoot {};
template<> struct PrimitiveRoot<998244353> { static constexpr int value = 3; };
template<> struct PrimitiveRoot<924844033> { static constexpr int value = 5; };

template<int MOD = 998244353>
void ntt(Integral<MOD> A[], int n, int inv) {
  // inv == 1: ntt, == -1: intt

  // MOD == a * b ^ k + 1, n <= b ^ k.
  // 998244353 == (7 * 17) * 2 ^ 23 + 1.
  // This code works only when b == 2.
  constexpr int primitive_root = PrimitiveRoot<MOD>::value;
  Integral<MOD> w = 1, d = Integral<MOD>(primitive_root).power((MOD - 1) / n), t;
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
  T get(int pos) const { return pos >= 0 && pos < size() ? (*this)[pos] : T(0); }
  T& touch(int pos) { if (pos >= size()) std::vector<T>::resize(pos + 1, T(0)); return (*this)[pos]; }
  Polynomial mod(int n) const { return Polynomial(std::vector<T>(this->data(), this->data() + std::min(n, size()))); }
};

template<typename T>
void ntt(Polynomial<T>& poly, int n, int inv) {
  if (poly.size() < n) poly.resize(n, 0);
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
  for (int i = 0; i < L; ++i) lhs[i] *= rhs[i];
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
Polynomial<T> operator*(const Polynomial<T>& p, T a) {
  return a * p;
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
  // NOTE: It equals to (poly % Polynomial<T>{-a, 1}).get(0).
}

template<typename T>
std::vector<T> multiple_point_eval(const Polynomial<T>& poly, const std::vector<T>& a) {  // Returns [eval(poly, w) for w in a]
  // https://www.luogu.com.cn/problem/P5050
  int m = a.size();
  std::vector<Polynomial<T>> bucket(m * 2 - 1);
  auto get_id = [](int l, int r) -> int {
    return (l + r) | (l != r);
  };
  std::function<void(int,int)> prepare = [&](int l, int r) -> void {
    Polynomial<T>& p = bucket[get_id(l, r)];
    if (l == r) {
      p = Polynomial<T>{-a[l], 1};
      return;
    }
    int mid = (l + r) >> 1;
    prepare(l, mid);
    prepare(mid + 1, r);
    p = bucket[get_id(l, mid)] * bucket[get_id(mid + 1, r)];
  };
  prepare(0, m - 1);
  std::vector<T> result(m);
  std::function<void(int, int, Polynomial<T>)> divide = [&](int l, int r, Polynomial<T> poly) -> void {
    poly = poly % bucket[get_id(l, r)];
    if (l == r) {
      result[l] = poly.get(0);
      return;
    }
    int mid = (l + r) >> 1;
    divide(l, mid, poly);
    divide(mid + 1, r, poly);
  };
  divide(0, m - 1, poly);
  return result;
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
  if (len == 0) len = ((int)poly.size() - 1) * int(k) + 1;
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

// a.k.a. Multiset counting.
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
  for (int i = 1; i < poly.size() && i < len; ++i) if (poly[i].val()) {
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

template<typename T>
Polynomial<T> lagrange_polynomial(const std::vector<T>& x, const std::vector<T>& y) {
  // https://en.wikipedia.org/wiki/Lagrange_polynomial
  // O(nlog^2(n)).
  if (x.empty()) return Polynomial<T>(1, T(0));

  int m = x.size();
  std::vector<Polynomial<T>> bucket(m * 2 - 1);
  auto get_id = [](int l, int r) -> int {
    return (l + r) | (l != r);
  };
  std::function<Polynomial<T>(int,int)> calc_g = [&](int l, int r) -> Polynomial<T> {
    Polynomial<T>& p = bucket[get_id(l, r)];
    if (l == r) {
      return p = Polynomial<T>{-x[l], 1};
    }
    int mid = (l + r) >> 1;
    return p = calc_g(l, mid) * calc_g(mid + 1, r);
  };
  std::vector<T> z(m);
  std::function<void(int, int, Polynomial<T>)> mp_eval = [&](int l, int r, Polynomial<T> poly) -> void {
    poly = poly % bucket[get_id(l, r)];
    if (l == r) {
      z[l] = poly.get(0);
      return;
    }
    int mid = (l + r) >> 1;
    mp_eval(l, mid, poly);
    mp_eval(mid + 1, r, poly);
  };
  mp_eval(0, m - 1, derivate(calc_g(0, (int)x.size() - 1)));
  std::function<Polynomial<T>(int,int)> divide = [&](int l, int r) -> Polynomial<T> {
    if (l == r) {
      return Polynomial<T>(1, y[l] / z[l]);;
    }
    int mid = (l + r) >> 1;
    return divide(l, mid) * bucket[get_id(mid + 1, r)] + divide(mid + 1, r) * bucket[get_id(l, mid)];
  };
  return divide(0, (int)x.size() - 1);
}

template<typename T>
T interpolation(const std::vector<T>& x, const std::vector<T>& y, const T& p) {
  return eval(lagrange_polynomial(x, y), p);
}

template<typename T>
Polynomial<T> eval_sum_from_l(const Polynomial<T>& poly, T l) {
  const int n = poly.size();
  std::vector<T> x;
  for (int i = 0; i <= n; ++i) x.emplace_back(l + i);
  std::vector<T> y = multiple_point_eval(poly, x);
  for (int i = 1; i < y.size(); ++i) y[i] += y[i - 1];
  return lagrange_polynomial(x, y);
}

template<typename T>
T eval_sum_over_segment(const Polynomial<T>& poly, T l, T r) {  // [l, r]
  // \sum_{x=l}^{r} eval(poly, x)
  return eval(eval_sum_from_l(poly, l), r);
}

template<typename T, typename OnLeaf>
void double_online_divide_and_conquer(OnLeaf&& on_leaf, int l, int r, const Polynomial<T>& A, Polynomial<T>& B) {
  // Note: The order of A and B matters, and you need to update Poly A yourself via `on_leaf`.
  if (l == r) {
    on_leaf(l, r);
    return;
  }
  int mid = (l + r) >> 1;
  auto update = [&](const Polynomial<T>& A, const Polynomial<T>& B, Polynomial<T>& output) {
    Polynomial<T> P, Q;
    for (int i = l; i <= mid; ++i) P.touch(i - l) = A.get(i);
    for (int i = 0; i <= std::min(r - l, mid); ++i) Q.touch(i) = B.get(i);
    Polynomial<T> W = P * Q;
    for (int i = mid + 1; i <= r; ++i) output.touch(i) += W.get(i - l);
  };
  double_online_divide_and_conquer(std::forward<OnLeaf>(on_leaf), l, mid, A, B);
  update(A, B, B);
  if (l > 1) update(B, A, B);
  double_online_divide_and_conquer(std::forward<OnLeaf>(on_leaf), mid + 1, r, A, B);
}

using Poly = Polynomial<Integral<MOD>>;

