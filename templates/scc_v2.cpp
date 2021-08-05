const int kN = 100000 + 5;

struct Edge {
  int v;
};

// Not verified.
struct StronglyConnectedComponent {
  int n;
  std::vector<int> dfn, low, belong, stack, instack;
  std::vector<std::vector<Edge>> edges;
  int tim = 0, top = 0, tot = 0;

  explicit StronglyConnectedComponent(int n)
    : n(n), dfn(n), low(n), belong(n), stack(n), instack(n), edges(n) {}
  virtual ~StronglyConnectedComponent() = default;

  void tarjan(int u) {
    dfn[u] = low[u] = ++tim;
    stack[top++] = u;
    instack[u] = 1;
    for (const Edge& e : edges[u]) {
      int v = e.v;
      if (!dfn[v]) {
        tarjan(v);
        low[u] = std::min(low[u], low[v]);
      } else if (instack[v]) {
        low[u] = std::min(low[u], dfn[v]);
      }
    }
    if (low[u] == dfn[u]) {
      while (true) {
        int v = stack[--top];
        instack[v] = 0;
        belong[v] = tot;
        if (v == u) break;
      }
      ++tot;
    }
  }

  void scc() {
    for (int i = 0; i < n; i ++) if (!dfn[i]) tarjan(i);
  }
};
