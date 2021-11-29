// https://en.wikipedia.org/wiki/Fast_Walsh%E2%80%93Hadamard_transform
template<typename T>
static void fwt(T* A, int n, int inv) {
  // [x^k]fwt(x^{a_i}) = (-1)^{__builtin_popcount(k & a_i)}
  //
  // n should be a power of 2.
  // inv == 1: forward; inv == -1: reverse.
  const T inv2 = T(1) / 2;
  for (int l = 1; l << 1 <= n; l <<= 1) {
    for (int s = 0; s < n; ++ s) {
      if (~s & l) {
        T a = A[s];
        T b = A[s ^ l];
        if (inv == 1) {
          A[s] = a + b;
          A[s ^ l] = a - b;
        } else {
          A[s] = (a + b) * inv2;
          A[s ^ l] = (a - b) * inv2;
        }
      }
    }
  }
}

