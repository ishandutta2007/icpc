using LL = long long;

LL exgcd(LL a, LL b, LL &x, LL &y) {
  if (b == 0)
    return x = 1, y = 0, a;
  LL g = exgcd(b, a % b, y, x);
  y -= a / b * x;
  return g;
}

// a * x + b * y == c
// 0 <= x <= lx
// 0 <= y <= ly
bool gao(LL a, LL b, LL c, LL lx, LL ly, LL &x, LL &y){
  LL g = exgcd(a, b, x, y);
  if (c % g) return false;
  a /= g; b /= g; c /= g;
  x *= c; y *= c;
  x = x % b - b - b + lx / b * b;
  while (x + b <= lx) x += b;
  if (x < 0) return false;
  y = (c - a * x) / b;
  if (y >= 0 && y <= ly) return true;
  if (y > ly) return false;
  LL d = (std::abs(y) + a - 1) / a;
  y += d * a; x -= d * b;
  return x >= 0 && x <= lx && y >= 0 && y <= ly;
}
