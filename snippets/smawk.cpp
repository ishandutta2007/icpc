struct Smawk {
 public:
  // Solve <max, +> convolution.
  // In O(n) time if one of the input array is concave.
  // In O(n^2) otherwise.
  // https://codeforces.com/blog/entry/98663
  //
  // <max, +> convolution means:
  // Given two arrays A and B, find an array C where
  // C_i = max_{j+k=i} (A_j + B_k).
  template<typename T>
  static std::vector<T> convolution(
      const std::vector<T>& A, const std::vector<T>& B) {
    if (concave_validation(B)) return convolution_with_concave_shape(A, B);
    if (concave_validation(A)) return convolution_with_concave_shape(B, A);
    return brute_convolution(A, B);
  }

  template<typename T>
  static std::vector<T> convolution_with_concave_shape(
      const std::vector<T>& any_shape, const std::vector<T>& concave_shape) {
    // assert(concave_validation(concave_shape));
    int n = any_shape.size(), m = concave_shape.size();
    if (n == 0 || m == 0) return {};
    auto func = [&](int i, int j) {
      return any_shape[j] + concave_shape[i - j];
    };
    auto cmp = [&](int i, int j, int k) {
      if(i < k) return false;
      if(i - j >= m) return true;
      return func(i, j) <= func(i, k);
    };
    const std::vector<int> best = smawk(cmp, n + m - 1, n);
    std::vector<T> ret(n + m - 1);
    for(int i = 0; i < n + m - 1; i++) ret[i] = func(i, best[i]);
    return ret;
  }

  template<typename T>
  static bool concave_validation(const std::vector<T>& B) {
    // The second derivative should be non-positive.
    int m = B.size();
    for (int i = 1; i + 1 < B.size(); ++i) {
      if (B[i] - B[i - 1] < B[i + 1] - B[i]) return false;
    }
    return true;
  }

  template<typename T>
  static std::vector<T> brute_convoluiton(
      const std::vector<T>& A, const std::vector<T>& B) {
    int n = A.size();
    int m = B.size();
    if (n == 0 || m == 0) return {};
    std::vector<T> C(n + m - 1);
    for (int i = 0; i < C.size(); ++i) {
      std::vector<T> tmp;
      for (int j = std::max(i - m + 1, 0); j <= std::min(i, n - 1); ++j) {
        tmp.emplace_back(A[j] + B[i - j]);
      }
      C[i] = *std::max_element(tmp.begin(), tmp.end());
    }
    return C;
  }

 private:
  // SMAWK for max.
  template<typename F>
  static std::vector<int> smawk(
      F&& f, const std::vector<int>& rows, const std::vector<int>& cols) {
    std::vector<int> ans(rows.size(), -1);
    if(std::max(rows.size(), cols.size()) <= 2) {
      for(int i = 0; i < rows.size(); ++i) {
        for(auto j : cols) {
          if(ans[i] == -1 || f(rows[i], ans[i], j)) ans[i] = j;
        }
      }
    } else if(rows.size() < cols.size()) {
      std::vector<int> stack;
      for(int j : cols) {
        while(true) {
          if(stack.empty()) {
            stack.push_back(j);
            break;
          } else if(f(rows[(int)stack.size() - 1], stack.back(), j)) {
            stack.pop_back();
          } else if(stack.size() < rows.size()) {
            stack.emplace_back(j);
            break;
          } else {
            break;
          }
        }
      }
      ans = smawk(f, rows, stack);
    } else {
      std::vector<int> new_rows;
      for(int i = 1; i < rows.size(); i += 2) new_rows.push_back(rows[i]);
      auto other_ans = smawk(f, new_rows, cols);
      for(int i = 0; i < new_rows.size(); i++) ans[2 * i + 1] = other_ans[i];
      for(int i = 0, l = 0, r = 0; i < rows.size(); i += 2) {
        while(l && cols[l - 1] >= ans[i - 1]) --l;
        if(i + 1 == rows.size()) r = cols.size();
        while(r < cols.size() && r <= ans[i + 1]) ++r;
        ans[i] = cols[l++];
        for(; l < r; ++l) {
          if(f(rows[i], ans[i], cols[l])) {
            ans[i] = cols[l];
          }
        }
        --l;
      }
    }
    return ans;
  }

  // max SMAWK
  // F(i, j, k) checks if M[i][j] <= M[i][k]
  // another interpretations is:
  // F(i, j, k) checks if M[i][k] is at least as good as M[i][j]
  // higher == better
  // when comparing 2 columns as vectors
  // for j < k, column j can start better than column k
  // as soon as column k is at least as good, it's always at least as good
  template<typename F>
  static std::vector<int> smawk(F&& f, int n, int m) {
    std::vector<int> rows(n), cols(m);
    std::iota(rows.begin(), rows.end(), 0);
    std::iota(cols.begin(), cols.end(), 0);
    return smawk(f, rows, cols);
  }
};

