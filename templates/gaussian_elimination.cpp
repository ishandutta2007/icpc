// T is required to be a field.
template<typename T>
struct GaussianElimination {
 public:
  static bool solve(std::vector<std::vector<T>>& A) {
    std::vector<T> extra_column(A.size());
    // Always true.
    return solve(A, extra_column, nullptr);
  }

  // Return true if the linear system is solvable.
  static bool solve(std::vector<std::vector<T>>& A, std::vector<T>& extra_column, std::vector<T>* nullable_solution = nullptr) {
    const int num_rows = A.size();
    assert(extra_column.size() == num_rows);
    if (num_rows == 0) return true;
    const int num_columns = A[0].size();

    int i, j, row, col, bestr;
    for (row = 0, col = 0; row < num_rows && col < num_columns; ++row, ++col) {
      for (; col < num_columns; ++col) {
        bestr = row;
        for (i = row + 1; i < num_rows; ++i) {
          if (better(A[i][col], A[bestr][col])) bestr = i;
        }
        if (better(A[bestr][col], 0)) break;
      }
      if (col == num_columns) break;
      if (row != bestr) {
        for (j = col; j < num_columns; ++j) std::swap(A[row][j], A[bestr][j]);
        std::swap(extra_column[row], extra_column[bestr]);
      }
      extra_column[row] /= A[row][col];
      for (j = col + 1; j < num_columns; ++j) A[row][j] /= A[row][col];
      A[row][col] = T(1);
      for (i = 0; i < num_rows; ++i) {
        if (i == row || A[i][col] == T(0)) continue;
        extra_column[i] -= extra_column[row] * A[i][col];
        for (j = col + 1; j < num_columns; ++j) A[i][j] -= A[row][j] * A[i][col];
        A[i][col] = 0;
      }
    }
    for (int r = row; r < num_rows; ++r) if (better(extra_column[r], 0)) return false;
    if (nullable_solution != nullptr) {
      nullable_solution->assign(num_columns, T(0));
      for (int r = 0, c = 0; r < row; ++r) {
        while (c < num_columns && !better(A[r][c], 0)) ++c;
        assert(c < num_columns);
        nullable_solution->at(c) = extra_column[r] / A[r][c];
      }
    }
    return true;
  }

  // Return true if the matrix A has an inversion.
  static bool matrix_inversion(std::vector<std::vector<T>> A, std::vector<std::vector<T>>* nullable_inversion = nullptr) {
    const int num_rows = A.size();
    if (num_rows == 0) {
      if (nullable_inversion != nullptr) {
        nullable_inversion->clear();
      }
      return true;
    }
    const int num_columns = A[0].size();
    if (num_rows != num_columns) return false;
    for (int r = 0; r < num_rows; ++r) {
      for (int c = 0; c < num_columns; ++c) {
        A[r].emplace_back(T(r == c ? 1 : 0));
      }
    }
    solve(A);
    for (int r = 0; r < num_rows; ++r) if (A[r][r] != T(1)) return false;
    if (nullable_inversion != nullptr) {
      nullable_inversion->assign(num_rows, std::vector<T>(num_columns, T(0)));
      for (int r = 0; r < num_rows; ++r) {
        for (int c = 0; c < num_columns; ++c) {
          (*nullable_inversion)[r][c] = A[r][c + num_columns];
        }
      }
    }
    return true;
  }

 private:
  // Return true if x is better than y.
  static bool better(T x, T y) {
    if constexpr(std::is_floating_point<T>::value) {
      constexpr T eps = 1e-8;
      return std::abs(x) > std::abs(y) + eps;
    } else {
      return x != 0;
    }
  }
};

void test() {
  std::vector<std::vector<double>> A{{2, 1, -1}, {-3, -1, 2}, {-2, 1, 2}};
  std::vector<double> X{8, -11, -3};
  GaussianElimination<double>::solve(A, X);
  DUMP(A);  // {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}}
  DUMP(X);  // {2, 3, -1}
}

