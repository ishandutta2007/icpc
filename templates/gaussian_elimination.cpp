template<typename T>
struct GaussianElimination {
  static int dcmp(T x) { constexpr T eps = 1e-8; return x < -eps ? -1 : x > eps; }

  static int solve(std::vector<std::vector<T>>& A, std::vector<T>& extra_column) {
    static_assert(std::is_floating_point<T>::value, "Only support floating point types");
    int i, j, k, col, maxr;
    int num_rows = A.size();
    assert(num_rows > 0);
    assert(extra_column.size() == num_rows);
    int num_columns = A[0].size();
    // Free variables are not handled.
    for (k = 0, col = 0; k < A.size() && col < num_columns; ++k, ++col) {
      while (col < num_columns) {
        maxr = k;
        for (i = k + 1; i < num_rows; ++i) {
          if (dcmp(std::abs(A[i][col]) - std::abs(A[maxr][col])) > 0) maxr = i;
        }
        if (dcmp(A[maxr][col]) != 0) break;
        ++col;
      }
      if (col == num_columns) break;
      if (k != maxr) {
        for (j = col; j < num_columns; ++j) std::swap(A[k][j], A[maxr][j]);
        std::swap(extra_column[k], extra_column[maxr]);
      }
      extra_column[k] /= A[k][col];
      for (j = col + 1; j < num_columns; ++j) A[k][j] /= A[k][col];
      A[k][col] = T(1);
      for (i = 0; i < num_rows; ++i) {
        if (i == k || A[i][col] == T(0)) continue;
        extra_column[i] -= extra_column[k] * A[i][col];
        for (j = col + 1; j < num_columns; ++j) A[i][j] -= A[k][j] * A[i][col];
        A[i][col] = 0;
      }
    }
    return 1;
  }
};

void test() {
  std::vector<std::vector<double>> A{{2, 1, -1}, {-3, -1, 2}, {-2, 1, 2}};
  std::vector<double> X{8, -11, -3};
  GaussianElimination<double>::solve(A, X);
  DUMP(A);  // {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}}
  DUMP(X);  // {2, 3, -1}
}

