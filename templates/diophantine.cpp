template<typename T>
T exgcd(T a, T b, T& x, T& y) {
  if (b == 0) return x = 1, y = 0, a;
  T g = exgcd(b, a % b, y, x);
  y -= a / b * x;
  return g;
}

// a * x + b * y == c
// g = |gcd(a, b)|
// |x|, |y| <= max(|a|, |b|, |c|)
template<typename T>
bool diophantine(T a, T b, T c, T& x, T& y, T& g) {
  if (a == 0 && b == 0) return c == 0 ? (x = y = g = 0, true) : false;
  if (a == 0) return (c % b == 0) ? (x = 0, y = c / b, g = std::abs(b), true) : false;
  if (b == 0) return (c % a == 0) ? (x = c / a, y = 0, g = std::abs(a), true) : false;
  g = exgcd(a, b, x, y);
  if (c % g != 0) return false;
  T dx = c / a;
  c -= dx * a;
  T dy = c / b;
  c -= dy * b;
  x = dx + T((__int128)x * (c / g) % b);
  y = dy + T((__int128)y * (c / g) % a);
  g = std::abs(g);
  return true;
}

template<typename T = long long>
bool chinese_remainder_theorem(T k1, T m1, T k2, T m2, T& k, T& m) {
  k1 %= m1;
  if (k1 < 0) k1 += m1;
  k2 %= m2;
  if (k2 < 0) k2 += m2;
  T x, y, g;
  if (!diophantine(m1, -m2, k2 - k1, x, y, g)) {
    return false;
  }
  T dx = m2 / g;
  T delta = x / dx - (x % dx < 0);
  k = m1 * (x - dx * delta) + k1;
  m = m1 / g * m2;
  assert(0 <= k && k < m);
  return true;
}

