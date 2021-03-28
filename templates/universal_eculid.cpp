const Mint inv2 = Mint(2).inv();

// f = \sum_{i}{floor((a * i + b) / c)}
// g = \sum_{i}{i * floor((a * i + b) / c)}
// h = \sum_{i}{floor((a * i + b) / c)^2}
struct Info {
  Mint f, g, h;
  Mint u, r;
};

const Info f0 = Info{.f = 0, .g = 0, .h = 0, .u = 0, .r = 0};
const Info fu = Info{.f = 0, .g = 0, .h = 0, .u = 1, .r = 0};
const Info fr = Info{.f = 0, .g = 0, .h = 0, .u = 0, .r = 1};

// Should be associative.
Info operator * (const Info& lhs, const Info& rhs) {
  Info ret;
  ret.u = lhs.u + rhs.u;
  ret.r = lhs.r + rhs.r;
  ret.f = lhs.u * rhs.r + lhs.f + rhs.f;
  ret.g = lhs.r * rhs.f + rhs.r * (rhs.r - 1) * inv2 * lhs.u + rhs.r * lhs.r * lhs.u + lhs.g + rhs.g;
  ret.h = lhs.u * rhs.f * 2 + lhs.u * lhs.u * rhs.r + lhs.h + rhs.h;
  return ret;
}

Info power(Info a, int b) {
  Info ret = f0;
  for (; b; b >>= 1, a = a * a) if (b & 1) ret = ret * a;
  return ret;
}

// Calculate f(s), where s is generated as follows:
// - Consider x in (0, n] incrementally.
// - Once line y=(ax+b)/c touches a integral horizontal line (y=z, z in Z), append a 'u' to s.
// - Once line y=(ax+b)/c touches a integral vertical line (x=z, z in Z), append a 'r' to s.
Info universal_euclid(int a, int b, int c, int n, const Info& fu, const Info& fr) {
  b %= c;
  if (a >= c) return universal_euclid(a % c, b, c, n, fu, power(fu, a / c) * fr);
  int m = (a * 1LL * n + b) / c;
  if (m == 0) return power(fr, n);
  return power(fr, (c - b - 1) / a) * fu * universal_euclid(c, c - b - 1, a, m - 1, fr, fu) * power(fr, n - (c * 1LL * m - b - 1) / a);
}

// https://www.luogu.com.cn/problem/P5170
void solve(int a, int b, int c, int n) {
  Info result = power(fu, b / c) * fr * universal_euclid(a, b % c, c, n, fu, fr);
  printf("%d %d %d\n", result.f.val(), result.h.val(), result.g.val());
}
