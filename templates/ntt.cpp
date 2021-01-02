using LL = long long;
const int ort = 3;  // primitive root of MOD.
const int MOD = 998244353;
// MOD == a * b ^ k + 1, n <= b ^ k.
// 998244353 == (7 * 17) * 2 ^ 23 + 1.
// This code works only when b == 2.

LL power(LL a, LL b, LL p) {
  LL ret = 1;
  for ( ; b; b >>= 1, a = a * a % p) if (b & 1) ret = ret * a % p;
  return ret;
}

void ntt(LL A[], int n, int inv) {
  // inv == 1: ntt, == -1: intt
  LL w = 1, d = power(ort, (MOD - 1) / n, MOD), t;
  int i, j, c, s;
  if (inv == -1) {
    for (i = 1, j = n - 1; i < j; ++i, --j) std::swap(A[i], A[j]);
    for (t = power(n, MOD - 2, MOD), i = 0; i < n; ++i) A[i] = A[i] * t % MOD;
  }
  for (s = n >> 1; s; s >>= w = 1, d = d * d % MOD) {
    for (c = 0; c < s; ++c, w = w * d % MOD) {
      for (i = c; i < n; i += s << 1) {
        A[i | s] = (A[i] + MOD - (t = A[i | s])) * w % MOD;
        A[i] = (A[i] + t) % MOD;
      }
    }
  }
  for (i = 1; i < n; ++i) {
    for (j = 0, s = i, c = n >> 1; c; c >>= 1,s >>= 1) j = j << 1 | (s & 1);
    if (i < j) std::swap(A[i], A[j]);
  }
}

