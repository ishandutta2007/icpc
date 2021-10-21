template<int MOD, template<int> typename Integral>
Integral<MOD> det(std::vector<std::vector<Integral<MOD>>> A) {
  if (A.empty() || A[0].size() != A.size()) return 0;
  Integral<MOD> ret = 1;
  const int n = A.size();
  for (int i = 0; i < n; ++ i) {
    if (A[i][i] == 0) {
      for (int j = i + 1; j < n; ++ j) {
        if (A[j][i].val()) {
          for (int k = i; k < n; ++ k) {
            std::swap(A[i][k], A[j][k]);
          }
          ret = -ret;
          break;
        }
      }
      if (A[i][i] == 0) return 0;
    }
    for (int j = i + 1; j < n; ++ j) {
      Integral<MOD> a = 1, b = 0, c = 0, d = 1;
      int x = A[i][i].val(), y = A[j][i].val();
      while (y) {
        int t = x / y;
        if (t < 0) t += MOD;
        a -= c * t;
        b -= d * t;
        std::swap(a, c);
        std::swap(b, d);
        x %= y;
        std::swap(x, y);
        ret = -ret;
      }
      for (int k = 0; k < n; ++ k) {
        Integral<MOD> q = A[i][k], w = A[j][k];
        A[i][k] = a * q + b * w;
        A[j][k] = c * q + d * w;
      }
    }
    ret *= A[i][i];
  }
  return ret;
}

