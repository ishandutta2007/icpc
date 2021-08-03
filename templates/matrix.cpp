using Vector = std::vector<Mint>;
using Matrix = std::vector<Vector>;

Matrix mul(const Matrix& lhs, const Matrix& rhs) {
  CHECK(lhs[0].size() == rhs.size());
  Matrix ret(lhs.size(), Vector(rhs[0].size()));
  for (int i = 0; i < lhs.size(); ++i) {
    for (int j = 0; j < rhs[0].size(); ++j) {
      for (int k = 0; k < lhs[0].size(); ++k) {
        ret[i][j] += lhs[i][k] * rhs[k][j];
      }
    }
  }
  return ret;
}

Mint det(Matrix A) {
  Mint ret = 1;
  int n = A.size();
  CHECK(A.size() == A[0].size());
  for (int i = 0; i < n; ++ i) {
    if (A[i][i].val() == 0) {
      for (int j = i + 1; j < n; ++ j) {
        if (A[j][i].val()) {
          for (int k = i; k < n; ++ k) {
            std::swap(A[i][k], A[j][k]);
          }
          ret = -ret;
          break;
        }
      }
      if (A[i][i].val() == 0) return 0;
    }
    for (int j = i + 1; j < n; ++ j) {
      Mint a = 1,b = 0,c = 0,d = 1;
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
        Mint q = A[i][k], w = A[j][k];
        A[i][k] = a * q + b * w;
        A[j][k] = c * q + d * w;
      }
    }
    ret *= A[i][i];
  }
  return ret;
}
