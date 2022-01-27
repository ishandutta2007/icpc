template<typename Edge>
struct Tree {
  int n = 0;
  std::vector<std::vector<Edge>> graph;
  std::vector<int> dfn, ed, rd, depth, parent, sz;
  int stmp = 0;

  explicit Tree(int n = 0) : n(n), graph(n), dfn(n), ed(n), rd(n), depth(n), parent(n), sz(n) {}

  void make(int root) {
    dfs(root, -1);
  }

  void dfs(int u, int fa) {
    sz[u] = 1;
    parent[u] = fa;
    depth[u] = fa == -1 ? 0 : depth[fa] + 1;
    rd[stmp] = u;
    dfn[u] = stmp++;
    for (const Edge& e : graph[u]) if (e.v != fa) {
      dfs(e.v, u);
      sz[u] += sz[e.v];
    }
    ed[u] = stmp - 1;
  }
};

