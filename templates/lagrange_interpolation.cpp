template<typename T>
using Polynomial = std::vector<T>;

template<typename T>
void norm(Polynomial<T>& p) {
  while (p.size() > 1 && p.back() == T(0)) p.pop_back();
}

template<typename T>
Polynomial<T> operator + (const Polynomial<T>& lhs, const Polynomial<T>& rhs) {
  Polynomial<T> ret = lhs;
  ret.resize(std::max(lhs.size(), rhs.size()), T(0));
  for (int i = 0; i < rhs.size(); ++i) ret[i] += rhs[i];
  norm(ret);
  return ret;
}

template<typename T>
Polynomial<T> operator * (const Polynomial<T>& lhs, const Polynomial<T>& rhs) {
  CHECK(lhs.size() + rhs.size() > 0);
  Polynomial<T> ret(lhs.size() + rhs.size() - 1, T(0));
  for (int i = 0; i < lhs.size(); ++i)
    for (int j = 0; j < rhs.size(); ++j)
      ret[i + j] += lhs[i] * rhs[j];
  return ret;
}

template<typename T>
Polynomial<T> lagrange_polynomial(const std::vector<T>& x, const std::vector<T>& y) {
  // https://en.wikipedia.org/wiki/Lagrange_polynomial
  CHECK(x.size() > 0);
  int degree = x.size() - 1;
  std::vector<std::vector<T>> f(degree + 1);
  f[0] = y;
  for (int i = 1; i <= degree; ++i)
    for (int j = 0; j <= degree - 1; ++j)
      f[i].emplace_back((f[i - 1][j + 1] - f[i - 1][j]) / (x[i + j] - x[j]));
  Polynomial<T> cur(1, T(1));
  Polynomial<T> ret(1, T(0));
  for (int i = 0; i <= degree; ++i) {
    ret = ret + cur * Polynomial<T>(1, f[i][0]);
    cur = cur * Polynomial<T>{T(-x[i]), T(1)};
  }
  return ret;
}

template<typename T>
T eval(const Polynomial<T>& a, const T& x) {
  T ret(0);
  for (int i = (int)a.size() - 1; i >= 0; --i)
    ret = ret * x + a[i];
  return ret;
}

template<typename T>
T interpolation(const std::vector<T>& x, const std::vector<T>& y, const T& p) {
  return eval(lagrange_polynomial(x, y), p);
}

template<typename T>
Polynomial<T> sum_from_l(const Polynomial<T>& a, int l, int n) {
  std::vector<T> x;
  for (int i = 0; i <= n; ++i) x.emplace_back(l + i);
  std::vector<T> y;
  T cur(0);
  for (int i = 0; i <= n; ++i) {
    cur += eval(a, x[i]);
    y.emplace_back(cur);
  }
  return lagrange_polynomial(x, y);
}

template<typename T>
T sum_over_segment(const Polynomial<T>& a, int l, int r) {  // [l, r]
  return eval(sum_from_l(a, l, a.size()), T(r));
}
