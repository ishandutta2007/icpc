const int kN = 100000 + 5;
int n, dfn[kN], rd[kN << 1], dr[kN << 1], stmp, depth[kN];
std::vector<int> edges[kN];

struct SparseTable {
  std::vector<std::vector<int>> u;
  std::vector<int> lg;
  void build(int a[], int n) {
    std::vector<std::vector<int>>(n, std::vector<int>(20)).swap(u);
    lg.resize(n + 10);
    lg[0] = -1;
    for (int i = 1; i < lg.size(); ++ i) lg[i] = lg[i >> 1] + 1;
    for (int i = 0; i < n; ++ i) u[i][0] = a[i];
    for (int j = 1; (1 << j) <= n; ++ j) {
      for (int i = 0; i + (1 << j) <= n; ++ i) {
        u[i][j] = std::min(u[i][j - 1], u[i + (1 << (j - 1))][j - 1]);
      }
    }
  }
  int ask(int a, int b) {
    int k = lg[b - a + 1];
    return std::min(u[a][k], u[b - (1 << k) + 1][k]);
  }
} st;

int get_lca(int a, int b) {
  if (dfn[a] > dfn[b]) std::swap(a, b);
  return rd[st.ask(dfn[a], dfn[b])];
}
int get_dis(int a, int b) { return depth[a] + depth[b] - 2 * depth[get_lca(a, b)]; }

void dfs(int u, int fa) {
  depth[u] = fa == -1 ? 0 : depth[fa] + 1;
  dfn[u] = stmp;
  dr[stmp] = stmp;
  rd[stmp ++] = u;
  for (int v : edges[u]) if (v != fa) {
    dfs(v, u);
    dr[stmp++] = dfn[u];
  }
}
