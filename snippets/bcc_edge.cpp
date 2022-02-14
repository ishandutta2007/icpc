template<typename Edge>
struct Graph {
  int n = 0;
  std::vector<std::vector<Edge>> graph;

  Graph() = default;
  explicit Graph(int n) : n(n), graph(n) {}

  int size() const { return n; }
};

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
    g.emplace_back(Edge{.v = u, .next = head[v]});
    head[v] = (int)g.size() - 1;
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

  template<typename Edge>
  Graph<Edge> shrink() const {
    Graph<Edge> result_graph(tot);
    for (int u = 0; u < n; ++u) {
      for (int i = head[u]; i != -1; i = g[i].next) {
        int v = g[i].v;
        if (belong[u] != belong[v]) {
          result_graph.graph[belong[u]].emplace_back(Edge{.v = belong[v]});
        }
      }
    }
    for (int u = 0; u < tot; ++u) {
      auto& vec = result_graph.graph[u];
      std::sort(vec.begin(), vec.end(), [&](const Edge& lhs, const Edge& rhs) {
        return lhs.v < rhs.v;
      });
      vec.erase(std::unique(vec.begin(), vec.end(), [&](const Edge& lhs, const Edge& rhs) {
        return lhs.v == rhs.v;
      }), vec.end());
    }
    return result_graph;
  }
};

