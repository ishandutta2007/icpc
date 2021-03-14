template<typename T>
T exgcd(T a, T b, T& x, T& y) {
  if (a == 0) {
    x = 0;
    y = 1;
    return b;
  }
  T p = b / a;
  T g = exgcd(b - p * a, a, y, x);
  x -= p * y;
  return g;
}

template<typename T>
bool diophantine(T a, T b, T c, T& x, T& y, T& g) {
  if (a == 0 && b == 0) {
    if (c == 0) {
      x = y = g = 0;
      return true;
    }
    return false;
  }
  if (a == 0) {
    if (c % b == 0) {
      x = 0;
      y = c / b;
      g = std::abs(b);
      return true;
    }
    return false;
  }
  if (b == 0) {
    if (c % a == 0) {
      x = c / a;
      y = 0;
      g = std::abs(a);
      return true;
    }
    return false;
  }
  g = exgcd(a, b, x, y);
  if (c % g != 0) {
    return false;
  }
  T dx = c / a;
  c -= dx * a;
  T dy = c / b;
  c -= dy * b;
  x = dx + T((__int128)x * (c / g) % b);
  y = dy + T((__int128)y * (c / g) % a);
  g = std::abs(g);
  return true;
  // |x|, |y| <= max(|a|, |b|, |c|)
}

bool crt(long long k1, long long m1, long long k2, long long m2, long long& k, long long& m) {
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
