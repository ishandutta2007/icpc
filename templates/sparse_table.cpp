template<typename T, bool kUseMax>
struct SparseTable {
  std::vector<std::vector<T>> u;
  std::vector<int> lg;
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
        if constexpr(kUseMax) {
          u[i][j] = std::max(u[i][j - 1], u[i + (1 << (j - 1))][j - 1]);
        } else {
          u[i][j] = std::min(u[i][j - 1], u[i + (1 << (j - 1))][j - 1]);
        }
      }
    }
  }
  T ask(int a, int b) {
    if (a > b) std::swap(a, b);
    int k = lg[b - a + 1];
    if constexpr(kUseMax) {
      return std::max(u[a][k], u[b - (1 << k) + 1][k]);
    } else {
      return std::max(u[a][k], u[b - (1 << k) + 1][k]);
    }
  }
};

SparseTable<int, true> st;

