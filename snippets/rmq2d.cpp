template<typename T, typename Comparator = std::less<T>>
struct SparseTable2D {
 public:
  SparseTable2D() = default;
  explicit SparseTable2D(const std::vector<std::vector<T>>& a) { build(a); }

  void build(const std::vector<std::vector<T>>& a) {
    assert(a.size() > 0);
    n = a.size();
    m = a[0].size();
    lg.resize(std::max(n, m) + 1);
    lg[0] = -1;
    for (int i = 1; i < lg.size(); ++i) {
      lg[i] = lg[i >> 1] + 1;
    }
    table.resize(lg[n] + 1, std::vector<std::vector<std::vector<T>>>(lg[m] + 1, std::vector<std::vector<T>>(n, std::vector<T>(m))));
    table[0][0] = a;
    for (int i = 0; i <= lg[n]; ++i) {
      for (int j = 0; j <= lg[m]; ++j) {
        if (i + j == 0) continue;
        for (int r = 0; r + (1 << i) <= n; ++r) {
          for (int c = 0; c + (1 << j) <= m; ++c) {
            if (i)
              table[i][j][r][c] = select(table[i - 1][j][r][c], table[i - 1][j][r + (1 << (i - 1))][c]);
            else
              table[i][j][r][c] = select(table[i][j - 1][r][c], table[i][j - 1][r][c + (1 << (j - 1))]);
          }
        }
      }
    }
  }

  T ask(int x0, int y0, int x1, int y1) const {
    assert(0 <= x0 && x0 <= x1 && x1 < n);
    assert(0 <= y0 && y0 <= y1 && y1 < m);
    int i = lg[x1 - x0 + 1];
    int j = lg[y1 - y0 + 1];
    x1 += -(1 << i) + 1;
    y1 += -(1 << j) + 1;
    return select({table[i][j][x0][y0], table[i][j][x0][y1], table[i][j][x1][y0], table[i][j][x1][y1]});
  }

 private:
  T select(const T& lhs, const T& rhs) const { return cmp(lhs, rhs) ? lhs : rhs; }
  T select(const std::vector<T>& vec) const { return *std::min_element(vec.begin(), vec.end(), cmp); }

  int n, m;
  std::vector<int> lg;
  std::vector<std::vector<std::vector<std::vector<T>>>> table;
  Comparator cmp;
};

