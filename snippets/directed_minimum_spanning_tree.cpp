struct DirectedMinimumSpanningTree {
  static constexpr int inf = std::numeric_limits<int>::max();

  struct Edge {
    int u, v, cost;
  };
  std::vector<Edge> g;

  void add_edge(int u, int v, int cost) {
    g.emplace_back(Edge{.u = u, .v = v, .cost = cost});
  }

  // Note: The root is fixed.
  // In case you want a floating-root directed MST, you can add a virtual root which connects to all
  // other points with an edge of large enough cost.
  int solve(int root, int n) {
    int m = g.size();
    std::vector<int> pre(n), idx(m), f(n), inc(n);
    int ret = 0; int u, v;
    while (true) {
      pre.resize(n);
      f.resize(n);
      inc.resize(n);
      std::fill(inc.begin(), inc.end(), inf);
      for (int i = 0; i < m; ++i) {
        u = g[i].u; v = g[i].v;
        if (g[i].cost < inc[v] && u != v) {
          pre[v] = u;
          inc[v] = g[i].cost;
        }
      }
      for (int i = 0; i < n; ++i) {
        if (i == root) continue;
        if (inc[i] == inf) return -1;
      }
      int circle = 0;
      std::fill(idx.begin(), idx.end(), -1);
      std::fill(f.begin(), f.end(), -1);
      inc[root] = 0;
      for (int i = 0; i < n; ++i) {
        ret += inc[i];
        int v = i;
        while (f[v] != i && idx[v] == -1 && v != root) {
          f[v] = i;
          v = pre[v];
        }
        if (v != root && idx[v] == -1) {
          for (int u = pre[v]; u != v; u = pre[u]) idx[u] = circle;
          idx[v] = circle++;
        }
      }
      if (circle == 0) break;
      for (int i = 0; i < n; ++i) {
        if (idx[i] == -1) idx[i] = circle++;
      }
      for (int i = 0; i < m; ++i) {
        v = g[i].v;
        g[i].u = idx[g[i].u];
        g[i].v = idx[g[i].v];
        if (g[i].u != g[i].v) {
          g[i].cost -= inc[v];
        }
      }
      n = circle;
      root = idx[root];
    }
    return ret;
  }
};

