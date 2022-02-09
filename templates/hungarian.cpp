struct Hungarian {
  int n, m;
  std::vector<std::vector<bool>> adj;
  std::vector<int> left;
  std::vector<bool> vis;

  Hungarian() = default;
  Hungarian(int n, int m) : n(n), m(m), adj(n, std::vector<bool>(m)), left(m, -1), vis(m) {}

  bool aug(int u) {
    for (int v = 0; v < m; ++v) if (!vis[v] && adj[u][v]) {
      vis[v] = true;
      if (left[v] == -1 || aug(left[v])) {
        left[v] = u;
        return true;
      }
    }
    return false;
  }

  int solve() {
    int ret = 0;
    for (int i = 0; i < n; ++i) {
      std::fill(vis.begin(), vis.end(), false);
      if (aug(i)) ++ret;
    }
    return ret;
  }
};

