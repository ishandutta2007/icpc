const int MOD = (int)1e9 + 7;
const int inv2 = MOD + 1 >> 1;
int A[1 << 18];

void fwt(int A[],int n,int inv) {
  // [x^k]fwt(x^{a_i}) = (-1)^{__builtin_popcount(k & a_i)}
  for (int l = 1; l << 1 <= n; l <<= 1) {
    for (int s = 0; s < n; ++ s) {
      if (~s & l) {
        int a = A[s];
        int b = A[s ^ l];
        if (inv == 1) {
          A[s] = (a + b) % MOD;
          A[s ^ l] = (a - b + MOD) % MOD;
        } else {
          A[s] = (a + b) * 1ll * inv2 % MOD;
          A[s ^ l] = (a - b + MOD) * 1ll * inv2 % MOD;
        }
      }
    }
  }
}
