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
//
// General solution:
//   xx = x + b / g * t
//   yy = y - a / g * t
//   for all t in Z
bool diophantine(long long a, long long b, long long c, long long& x, long long& y, long long& g) {
  if (a == 0 && b == 0) return c == 0 ? (x = y = g = 0, true) : false;
  if (a == 0) return (c % b == 0) ? (x = 0, y = c / b, g = std::abs(b), true) : false;
  if (b == 0) return (c % a == 0) ? (x = c / a, y = 0, g = std::abs(a), true) : false;
  g = exgcd(a, b, x, y);
  if (c % g != 0) return false;
  long long dx = c / a;
  c -= dx * a;
  long long dy = c / b;
  c -= dy * b;
  x = dx + (long long)((__int128)x * (c / g) % b);
  y = dy + (long long)((__int128)y * (c / g) % a);
  g = std::abs(g);
  return true;
}

bool chinese_remainder_theorem(long long k1, long long m1, long long k2, long long m2, long long& k, long long& m) {
  k1 %= m1;
  if (k1 < 0) k1 += m1;
  k2 %= m2;
  if (k2 < 0) k2 += m2;
  long long x, y, g;
  if (!diophantine(m1, -m2, k2 - k1, x, y, g)) {
    return false;
  }
  long long dx = m2 / g;
  long long delta = x / dx - (x % dx < 0);
  k = m1 * (x - dx * delta) + k1;
  m = m1 / g * m2;
  assert(0 <= k && k < m);
  return true;
}

