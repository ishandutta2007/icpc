struct TwoSat {
 public:
  int n;
  std::vector<int> head;
  std::vector<int> stack;
  std::vector<bool> mark;

  struct Edge {
    int v, next;
  };
  std::vector<Edge> g;

  explicit TwoSat(int n) : n(n), head(n, -1), mark(n, false) {}

  void add_edge(int u, int v) {
    g.emplace_back(Edge{.v = v, .next = head[u]});
    head[u] = (int)g.size() - 1;
  }

  bool solve() {
    for (int i = 0; i < n; i += 2) {
      if (!mark[i] && !mark[i + 1]) {
        stack.clear();
        if (!dfs(i)) {
          while (!stack.empty()) {
            int v = stack.back(); stack.pop_back();
            mark[v] = false;
          }
          if (!dfs(i + 1)) return false;
        }
      }
    }
    return true;
  }

 private:
  bool dfs(int u) {
    if (mark[u ^ 1]) return false;
    if (mark[u]) return true;
    mark[u] = true;
    stack.emplace_back(u);
    for (int i = head[u]; i != -1; i = g[i].next) {
      int v = g[i].v;
      if (!dfs(v)) return false;
    }
    return true;
  }
};

