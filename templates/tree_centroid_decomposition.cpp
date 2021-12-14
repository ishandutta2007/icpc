template<typename Edge>
struct TreeCentroidDecomposition {
  int n = 0;
  std::vector<std::vector<Edge>> graph;

  std::vector<int> parent, sz, balance;
  std::vector<bool> vis;
  std::vector<int> que;

  explicit TreeCentroidDecomposition(int n) : n(n), graph(n), parent(n), sz(n), balance(n), vis(n) {}

  void divide_core(int root, int tot, int level) {
  }

  void divide(int root, int level) {
    int tot = bfs(root);
    for (int i = tot - 1; i > 0; --i) if (balance[que[i]] < balance[root]) root = que[i];
    bfs(root);

    divide_core(root, tot, level);

    vis[root] = true;
    for (const Edge& e : graph[root]) if (!vis[e.v]) divide(e.v, level + 1);
  }

  int bfs(int source, int fa = -1) {
    int qf = 0;
    que.clear();
    que.emplace_back(source);
    parent[source] = fa;
    while (qf < que.size()) {
      int u = que[qf++];
      sz[u] = 1;
      balance[u] = 0;
      for (const Edge& e : graph[u]) {
        int v = e.v;
        if (!vis[v] && parent[u] != v) {
          parent[v] = u;
          que.emplace_back(v);
        }
      }
    }
    for (int i = (int)que.size() - 1; i >= 0; --i) {
      int u = que[i];
      if (i) {
        sz[parent[u]] += sz[u];
        balance[parent[u]] = std::max(balance[parent[u]], sz[u]);
      }
      balance[u] = std::max(balance[u], (int)que.size() - sz[u]);
    }
    return que.size();
  }
};

