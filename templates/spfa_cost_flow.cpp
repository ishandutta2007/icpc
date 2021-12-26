template<typename T>
struct CostFlow {
 public:
  const T inf = std::numeric_limits<T>::max();
  int n = 0;
  int s = -1, t = -1;
  std::vector<int> head, prevv, preve;
  std::vector<T> dist;

  struct Edge {
    int v, next;
    T cap, cost;
  };
  std::vector<Edge> g;

  CostFlow() = default;
  explicit CostFlow(int n) : n(n), head(n, -1), prevv(n), preve(n), dist(n, inf) {}

  void add_edge(int u, int v, T cap, T cost) {
    g.emplace_back(Edge{.v = v, .next = head[u], .cap = cap, .cost = cost});
    head[u] = (int)g.size() - 1;
    g.emplace_back(Edge{.v = u, .next = head[v], .cap = 0, .cost = -cost});
    head[v] = (int)g.size() - 1;
  }

  std::pair<T, T> mcmf(int s, int t) {  // <flow, cost>
    this->s = s;
    this->t = t;
    T flow = 0, cost = 0;
    while (true) {
      spfa(s);
      if (dist[t] == inf) break;
      T f = inf;
      for (int u = t; u != s; u = prevv[u])
        f = std::min(f, g[preve[u]].cap);
      cost += f * dist[t];
      flow += f;
      for (int u = t; u != s; u = prevv[u])
        g[preve[u]].cap -= f, g[preve[u] ^ 1].cap += f;
    }
    return std::make_pair(flow, cost);
  }

  std::vector<std::tuple<int, int, T, T>> get_cuts(int s, int t) const {  // <u, v, original_cap, cost>
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
        cuts.emplace_back(u, g[i].v, g[i ^ 1].cap, g[i].cost);
      }
    }
    return cuts;
  }

 private:
  void spfa(int source) {
    std::vector<bool> inq(n);
    std::queue<int> que;
    std::fill(dist.begin(), dist.end(), inf);
    dist[source] = 0;
    que.emplace(source);
    while (!que.empty()) {
      int u = que.front(); inq[u] = false; que.pop();
      for (int i = head[u]; i != -1; i = g[i].next) {
        Edge& e = g[i];
        if (e.cap && dist[e.v] > dist[u] + e.cost) {
          dist[e.v] = dist[u] + e.cost;
          prevv[e.v] = u; preve[e.v] = i;
          if (!inq[e.v]) {
            que.emplace(e.v);
            inq[e.v] = true;
          }
        }
      }
    }
  }
};

