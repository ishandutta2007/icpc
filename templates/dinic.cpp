template<typename T>
struct MaxFlow {
 public:
  int n = 0;
  int s = -1, t = -1;
  std::vector<int> head, cur, dis;

  struct Edge {
    int v, next;
    T cap;
  };
  std::vector<Edge> g;

  MaxFlow() = default;
  explicit MaxFlow(int n) : n(n), head(n, -1), cur(n), dis(n) {}

  void add_edge(int u, int v, T cap) {
    g.emplace_back(Edge{.v = v, .next = head[u], .cap = cap});
    head[u] = (int)g.size() - 1;
    g.emplace_back(Edge{.v = u, .next = head[v], .cap = 0});
    head[v] = (int)g.size() - 1;
  }

  T dinic(int s, int t) {
    this->s = s;
    this->t = t;
    T flow = 0;
    while (bfs()) flow += dfs(s, std::numeric_limits<T>::max());
    return flow;
  }

  std::vector<std::tuple<int, int, T>> get_cuts(int s, int t) const {
    std::vector<bool> mark(n);
    std::function<void(int)> remark = [&](int u) {
      if (mark[u]) return;
      mark[u] = true;
      for (int i = head[u]; i != -1; i = g[i].next) {
        if (g[i].cap) remark(g[i].v);
      }
    };
    remark(s);
    std::vector<std::tuple<int, int, T>> cuts;
    for (int u = 0; u < n; ++u) if (mark[u]) {
      for (int i = head[u]; i != -1; i = g[i].next) if (!mark[g[i].v]) {
        assert(g[i].cap == 0);
        cuts.emplace_back(u, g[i].v, g[i ^ 1].cap);
      }
    }
    return cuts;
  }

 private:
  bool bfs() {
    std::queue<int> que;
    std::fill(dis.begin(), dis.end(), -1);
    cur = head;
    dis[t] = n;
    que.emplace(t);
    while (!que.empty()) {
      int u = que.front(); que.pop();
      for (int i = head[u]; i != -1; i = g[i].next) {
        Edge& e = g[i];
        if (g[i ^ 1].cap && dis[e.v] == -1) {
          dis[e.v] = dis[u] - 1;
          que.emplace(e.v);
        }
      }
    }
    return dis[s] != -1;
  }

  T dfs(int u, T a) {
    if (u == t) return a;
    T flow = 0, f = 0;
    for (int& i = cur[u]; i != -1; i = g[i].next) {
      Edge& e = g[i];
      if (e.cap && dis[e.v] > dis[u]) {
        f = dfs(e.v, std::min(a, e.cap));
        flow += f;
        e.cap -= f;
        g[i ^ 1].cap += f;
        a -= f;
        if (a == 0) break;
      }
    }
    if (flow == 0) dis[u] = -1;
    return flow;
  }
};

