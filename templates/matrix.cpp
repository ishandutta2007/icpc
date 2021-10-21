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
