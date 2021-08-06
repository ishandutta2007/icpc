struct Edge {
  int v = 0;
  int w = 1;
  Edge(int v, int w = 1) : v(v), w(w) {}
};

struct DirectedAcyclicGraph {
  int n;
  std::vector<std::vector<Edge>> edges;

  explicit DirectedAcyclicGraph(int n) : n(n), edges(n) {}

  std::vector<int> get_topological_order() const {
    std::vector<int> degree(n);
    for (int u = 0; u < n; ++u) {
      for (const Edge& e : edges[u]) {
        degree[e.v]++;
      }
    }
    std::vector<int> vec;
    for (int u = 0; u < n; ++u) if (degree[u] == 0) {
      vec.emplace_back(u);
    }
    for (int at = 0; at < vec.size(); ++at) {
      int u = vec[at];
      for (const Edge& e : edges[u]) {
        if (--degree[e.v] == 0) {
          vec.emplace_back(e.v);
        }
      }
    }
    return vec;
  }
};

struct StronglyConnectedComponent {
  int n;
  std::vector<int> dfn, low, belong, stack, instack;
  std::vector<std::vector<Edge>> edges;
  int tim = 0, top = 0, tot = 0;
  std::vector<int> cardinality;

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
    cardinality.resize(tot);
    for (int i = 0; i < n; ++i) {
      cardinality[belong[i]]++;
    }
  }

  DirectedAcyclicGraph shrink() const {
    DirectedAcyclicGraph dag(tot);
    for (int u = 0; u < n; ++u) {
      for (const Edge& e : edges[u]) {
        int v = e.v;
        if (belong[u] != belong[v]) {
          dag.edges[belong[u]].emplace_back(belong[v]);
        }
      }
    }
    return dag;
  }
};
