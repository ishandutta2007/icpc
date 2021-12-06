template<typename T, typename Comparator = std::less<T>>
struct SparseTable {
 public:
  void build(const std::vector<T>& a) {
    int n = a.size(), L = 1;
    while ((1 << L) <= n) ++L;
    std::vector<std::vector<T>>(n, std::vector<T>(L)).swap(u);
    lg.resize(n + 1);
    lg[0] = -1;
    for (int i = 1; i < lg.size(); ++ i) lg[i] = lg[i >> 1] + 1;
    for (int i = 0; i < n; ++ i) u[i][0] = a[i];
    for (int j = 1; (1 << j) <= n; ++ j) {
      for (int i = 0; i + (1 << j) <= n; ++ i) {
        u[i][j] = select(u[i][j - 1], u[i + (1 << (j - 1))][j - 1]);
      }
    }
  }
  T ask(int a, int b) const {  // [a, b]
    if (a > b || a < 0 || b >= u.size()) throw;
    int k = lg[b - a + 1];
    return select(u[a][k], u[b - (1 << k) + 1][k]);
  }
  int size() const { return u.size(); }
 private:
  T select(const T& lhs, const T& rhs) const { return cmp(lhs, rhs) ? lhs : rhs; }

  std::vector<std::vector<T>> u;
  std::vector<int> lg;
  Comparator cmp;
};

// SparseTable<int> st;
// SparseTable<int, std::greater<int>> st;

