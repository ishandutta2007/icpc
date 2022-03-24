struct TwoSat {
 public:
  explicit TwoSat(int n = 0) : num_variables(n), mark(num_variables << 1, false), graph(num_variables << 1) {}

  // clause_1 \cap clause_2 \cap ... \cap clause_m,
  // where clause is in the form of `(x_fx \cap y_fy)`,
  // x and y are both boolean variables, and x_fx means x takes the boolean value fx.
  void add_clause(int x, bool fx, int y, bool fy) {
    add_edge(x << 1 | !fx, y << 1 | fy);
    add_edge(y << 1 | !fy, x << 1 | fx);
  }

  void add_edge(int u, int v) { graph[u].emplace_back(Edge{.v = v}); }

  bool solve() {
    for (int i = 0; i < num_variables; ++i) if (!mark[i << 1] && !mark[i << 1 | 1]) {
      stack.clear();
      if (!dfs(i << 1)) {
        while (!stack.empty()) {
          int v = stack.back(); stack.pop_back();
          mark[v] = false;
        }
        if (!dfs(i << 1 | 1)) return false;
      }
    }
    return true;
  }

  std::vector<bool> get_solution() const {
    std::vector<bool> solution(num_variables);
    for (int i = 0; i < num_variables; ++i) solution[i] = mark[i << 1 | 1];
    return solution;
  }

 private:
  int num_variables = 0;
  std::vector<int> stack;
  std::vector<bool> mark;

  struct Edge {
    int v;
  };
  std::vector<std::vector<Edge>> graph;

  bool dfs(int u) {
    if (mark[u ^ 1]) return false;
    if (mark[u]) return true;
    mark[u] = true;
    stack.emplace_back(u);
    for (const Edge& e : graph[u]) {
      if (!dfs(e.v)) return false;
    }
    return true;
  }
};

