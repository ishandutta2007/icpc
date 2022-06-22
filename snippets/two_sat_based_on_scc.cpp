template<typename Edge>
struct DirectedAcyclicGraph {
  int n;
  std::vector<std::vector<Edge>> graph;

  explicit DirectedAcyclicGraph(int n = 0) : n(n), graph(n) {}

  std::vector<int> get_topological_order() const {
    std::vector<int> degree(n);
    for (int u = 0; u < n; ++u) {
      for (const Edge& e : graph[u]) {
        degree[e.v]++;
      }
    }
    std::vector<int> vec;
    for (int u = 0; u < n; ++u) if (degree[u] == 0) {
      vec.emplace_back(u);
    }
    for (int at = 0; at < vec.size(); ++at) {
      int u = vec[at];
      for (const Edge& e : graph[u]) {
        if (--degree[e.v] == 0) {
          vec.emplace_back(e.v);
        }
      }
    }
    return vec;
  }
};

template<typename Edge>
struct StronglyConnectedComponent {
  int n;
  std::vector<int> dfn, low, belong, stack, instack;
  std::vector<std::vector<Edge>> graph;
  int tim = 0, top = 0, tot = 0;
  std::vector<int> cardinality;

  StronglyConnectedComponent() = default;
  explicit StronglyConnectedComponent(int n)
    : n(n), dfn(n), low(n), belong(n), stack(n), instack(n), graph(n) {}
  virtual ~StronglyConnectedComponent() = default;

  void tarjan(int u) {
    dfn[u] = low[u] = ++tim;
    stack[top++] = u;
    instack[u] = 1;
    for (const Edge& e : graph[u]) {
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

  DirectedAcyclicGraph<Edge> shrink() const {
    DirectedAcyclicGraph<Edge> dag(tot);
    for (int u = 0; u < n; ++u) {
      for (const Edge& e : graph[u]) {
        int v = e.v;
        if (belong[u] != belong[v]) {
          dag.graph[belong[u]].emplace_back(Edge{.v = belong[v]});
        }
      }
    }
    return dag;
  }
};

struct TwoSat {
 public:
  explicit TwoSat(int n = 0) : num_variables(n), scc(num_variables << 1) {}

  // clause_1 \cap clause_2 \cap ... \cap clause_m,
  // where clause is in the form of `(x_fx \cup y_fy)`,
  // x and y are both boolean variables, and x_fx means x takes the boolean value fx.
  void add_clause(int x, bool fx, int y, bool fy) {
    add_edge(x << 1 | !fx, y << 1 | fy);
    add_edge(y << 1 | !fy, x << 1 | fx);
  }

  bool solve() {
    scc.scc();
    for (int i = 0; i < num_variables; ++i) {
      if (scc.belong[i << 1] == scc.belong[i << 1 | 1]) return false;
    }
    return true;
  }

  std::vector<bool> get_solution() const {
    std::vector<bool> solution(num_variables);
    for (int i = 0; i < num_variables; ++i) {
      solution[i] = scc.belong[i << 1] > scc.belong[i << 1 | 1];
    }
    return solution;
  }

  void add_edge(int u, int v) { scc.graph[u].emplace_back(Edge{.v = v}); }

 private:
  struct Edge {
    int v;
  };
  int num_variables = 0;
  StronglyConnectedComponent<Edge> scc;
};

