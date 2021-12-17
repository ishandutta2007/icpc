template<typename Edge>
struct ShrinkedGraph {
  std::vector<std::vector<Edge>> graph;
  std::vector<bool> is_cut;

  explicit ShrinkedGraph(int n) : graph(n), is_cut(n) {}

  int size() const { return graph.size(); }

  int add_point() {
    int u = graph.size();
    graph.emplace_back();
    is_cut.emplace_back();
    return u;
  }

  void remove_redundant_edges() {
    for (int u = 0; u < graph.size(); ++u) {
      std::sort(graph[u].begin(), graph[u].end(), [](const Edge& lhs, const Edge& rhs) {
        return lhs.v < rhs.v;
      });
      graph[u].erase(std::unique(graph[u].begin(), graph[u].end(), [](const Edge& lhs, const Edge& rhs) {
        return lhs.v == rhs.v;
      }), graph[u].end());
    }
  }
};

struct VertexBiconnectedComponent {
  int n = 0, m = 0;
  std::vector<int> dfn, low;  // Note: Unusual dfn.
  std::vector<int> head, belong;
  std::vector<bool> is_cut, visited;
  std::vector<int> stack;
  int btot = 0;

  struct Edge {
    int v = 0, next = -1, belong = -1;
    bool visited = false, is_cut = false;
  };
  std::vector<Edge> g;

  VertexBiconnectedComponent() = default;
  VertexBiconnectedComponent(int n, int m) : n(n), m(m), dfn(n, -1), low(n), head(n, -1), belong(n, -1), is_cut(n), visited(n) {}

  void add_edge(int u, int v) {
    g.emplace_back(Edge{.v = v, .next = head[u]});
    head[u] = (int)g.size() - 1;
    g.emplace_back(Edge{.v = u, .next = head[v]});
    head[v] = (int)g.size() - 1;
  }

  void tarjan(int u, int root, int tim) {
    dfn[u] = low[u] = tim;
    visited[u] = true;
    int child_count = 0;
    for (int i = head[u]; i != -1; i = g[i].next) {
      Edge &e = g[i];
      if (e.visited) continue;
      stack.emplace_back(i);
      g[i].visited = g[i ^ 1].visited = true;
      if (visited[e.v]) {
        low[u] = std::min(low[u], dfn[e.v]);
        continue;
      }
      tarjan(e.v, root, tim + 1);
      g[i].is_cut = g[i ^ 1].is_cut = (low[e.v] > dfn[u] || g[i].is_cut);
      if (u != root) is_cut[u] = is_cut[u] || (low[e.v] >= dfn[u]);
      if (low[e.v] >= dfn[u] || u == root) {
        while (true) {
          int id = stack.back(); stack.pop_back();
          g[id].belong = g[id ^ 1].belong = btot;
          if (id == i) break;
        }
        btot++;
      }
      low[u] = std::min(low[e.v], low[u]);
      child_count++;
    }
    if (u == root && child_count > 1) is_cut[u] = true;
  }

  void bcc() {
    for (int i = 0; i < n; ++i) if (!visited[i]) tarjan(i, i, 0);
  }

  template<typename ShrinkedEdge>
  ShrinkedGraph<ShrinkedEdge> build() {
    ShrinkedGraph<ShrinkedEdge> shrinked_graph(btot);
    for (int u = 0; u < n; ++u) {
      if (is_cut[u] || head[u] == -1) {
        int id = shrinked_graph.add_point();
        belong[u] = id;
        for (int i = head[u]; i != -1; i = g[i].next) {
          const Edge &e = g[i];
          int v = e.belong;
          shrinked_graph.graph[id].emplace_back(ShrinkedEdge{.v = v});
          shrinked_graph.graph[v].emplace_back(ShrinkedEdge{.v = id});
        }
      }
    }
    btot = shrinked_graph.size();
    shrinked_graph.remove_redundant_edges();
    for (int i = 0; i < m; ++i) {
      int u = g[i << 1].v;
      int v = g[i << 1 | 1].v;
      if (!is_cut[u]) belong[u] = g[i << 1].belong; else shrinked_graph.is_cut[belong[u]] = true;
      if (!is_cut[v]) belong[v] = g[i << 1].belong; else shrinked_graph.is_cut[belong[v]] = true;
    }
    return shrinked_graph;
  }
};

