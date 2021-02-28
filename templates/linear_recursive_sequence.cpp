#include <bits/stdc++.h>
#ifdef ALGO
#include "el_psy_congroo.hpp"
#else
#define DUMP(...) 1145141919810
#define CHECK(...) (__VA_ARGS__)
#endif

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
Polynomial<T> operator - (const Polynomial<T>& lhs, const Polynomial<T>& rhs) {
  Polynomial<T> ret = lhs;
  ret.resize(std::max(lhs.size(), rhs.size()), T(0));
  for (int i = 0; i < rhs.size(); ++i) ret[i] -= rhs[i];
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
  norm(ret);
  return ret;
}

template<typename T>
Polynomial<T> operator * (T a, Polynomial<T> p) {
  for (int i = 0; i < p.size(); ++i) p[i] *= a;
  norm(p);
  return p;
}

template<typename T, typename Poly>
struct LinearRecursiveSequenceSolver {
  static T solve(const Poly& seq, long long n) {
    if (n < seq.size()) return seq[n];
    const Poly coef = berlekamp_massey(seq);
    CHECK(!coef.empty() && coef.back() == T(1));
    const Poly p = power(Poly{T(0), T(1)}, n, coef);
    T ret = 0;
    for (int i = 0; i < p.size(); ++i) {
      ret += seq[i] * p[i];
    }
    return ret;
  }

  // https://en.m.wikipedia.org/wiki/Berlekamp–Massey_algorithm
  static Poly berlekamp_massey(const Poly& seq) {
    Poly C(1, 1);
    Poly B(1, 1);
    int L = 0;
    int m = 1;
    T b = 1;
    for (int n = 0; n < seq.size(); ++n) {
      T d = seq[n];
      for (int i = 1; i <= L && i < C.size(); ++i) d += C[i] * seq[n - i];
      if (d == T(0)) {
        ++m;
      } else if (2 * L <= n) {
        Poly tmp = C;
        Poly R = B;
        R.insert(R.begin(), m, 0);
        C = C - d / b * R;
        L = n + 1 - L;
        B = tmp;
        b = d;
        m = 1;
      } else {
        Poly R = B;
        R.insert(R.begin(), m, 0);
        C = C - d / b * R;
        ++m;
      }
    }
    std::reverse(C.begin(), C.end());
    CHECK(!C.empty() && C.back() == T(1));
    return C;
  }

  static Poly reduce(Poly p, const Poly& coef) {
    CHECK(!coef.empty() && coef.back() == T(1));
    int m = (int)coef.size() - 1;
    for (int i = (int)p.size() - 1; i >= m; --i) if (p[i].val()) {
      T v = p[i];
      for (int j = 0; j <= m; ++j)
        p[i - m + j] -= v * coef[j];
    }
    norm(p);
    return p;
  }

  static Poly power(Poly P, long long n, const Poly& coef) {
    Poly ret(P.size());
    ret[0] = 1;
    while (n) {
      if (n & 1) ret = reduce(ret * P, coef);
      P = reduce(P * P, coef);
      n >>= 1;
    }
    return ret;
  }
};

// using LinearRecSeqSolver = LinearRecursiveSequenceSolver<Integral<MOD>, Polynomial<Integral<MOD>>>;
