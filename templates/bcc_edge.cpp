struct BiconnectedComponent {
  struct Edge {
    int v, next;
  };

  int n = 0;
  std::vector<int> head;
  std::vector<Edge> g;
  std::vector<int> dfn, low, belong;
  std::vector<int> stack;
  int stmp = 0;
  int tot = 0;

  BiconnectedComponent() = default;
  explicit BiconnectedComponent(int n) : n(n), head(n, -1), dfn(n, -1), low(n), belong(n) {}

  void add_edge(int u, int v) {
    g.emplace_back(Edge{.v = v, .next = head[u]});
    head[u] = (int)g.size() - 1;
  }

  void tarjan(int u, int pree) {
    dfn[u] = low[u] = stmp++;
    stack.emplace_back(u);
    for (int i = head[u]; i != -1; i = g[i].next) {
      int v = g[i].v;
      if ((pree ^ i) == 1) continue;
      if (dfn[v] == -1) tarjan(v, i);
      low[u] = std::min(low[u], low[v]);
    }
    if (dfn[u] == low[u]) {
      while (true) {
        int v = stack.back(); stack.pop_back();
        belong[v] = tot;
        if (v == u) break;
      }
      tot++;
    }
  }

  void bcc() {
    for (int i = 0; i < n; ++i) {
      if (dfn[i] == -1) tarjan(i, -1);
    }
  }
};

