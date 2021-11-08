template<typename Edge>
struct HeavyLightDecomposition {
  int n = 0;
  std::vector<std::vector<Edge>> graph;
  std::vector<int> header, dfn, rd, parent, depth, sz;
  int tim = 0;

  explicit HeavyLightDecomposition(int n) : n(n), graph(n), header(n), dfn(n), rd(n), parent(n), depth(n), sz(n) {}

  void make() {
    get_sz(0, -1);
    rebuild(0, -1, 0);
  }

  void get_sz(int u, int fa) {
    sz[u] = 1;
    for (const Edge& e : graph[u]) {
      int v = e.v;
      if (v == fa) continue;
      get_sz(v, u);
      sz[u] += sz[v];
    }
  }

  void rebuild(int u, int fa, int color) {
    rd[tim] = u;
    dfn[u] = tim ++;
    parent[u] = fa;
    depth[u] = fa == -1 ? 0 : depth[fa] + 1;
    header[u] = color;
    int p = -1;
    for (const Edge& e : graph[u]) {
      int v = e.v;
      if (v == fa) continue;
      if (p == -1 || sz[v] > sz[p]) {
        p = v;
      }
    }
    if (p != -1) {
      rebuild(p,u,color);
    }
    for (const Edge& e : graph[u]) {
      int v = e.v;
      if (v == fa || v == p) continue;
      rebuild(v,u,v);
    }
  }

  int get_lca(int a, int b) {
    int ret = a;
    traverse([&ret, this](int side, int L, int R) {
      ret = this->rd[L];
    }, a, b);
    return ret;
  }

  // Handler() :: void operator () (int side, int L, int R).
  template<typename Handler>
  Handler traverse(Handler&& handler, int a, int b) {
    while (header[a] != header[b]) {
      if (depth[header[a]] > depth[header[b]]) {
        handler(0, dfn[header[a]], dfn[a]);
        a = parent[header[a]];
      } else {
        handler(1, dfn[header[b]], dfn[b]);
        b = parent[header[b]];
      }
    }
    if (dfn[a] < dfn[b]) {
      handler(1, dfn[a], dfn[b]);
    } else {
      handler(0, dfn[b], dfn[a]);
    }
    return handler;
  }
};

