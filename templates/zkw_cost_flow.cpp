template<typename T>
struct CostFlow {
 public:
  static constexpr T inf = std::numeric_limits<T>::max();
  int n = 0;
  int s = -1, t = -1;
  std::vector<bool> vis;
  std::vector<T> d;
  std::vector<int> head, cur;

  struct Edge {
    int v;
    T cap, cost;
    int next;
  };
  std::vector<Edge> g;

  CostFlow() = default;
  explicit CostFlow(int n) : n(n), vis(n), d(n), head(n, -1), cur(n) {}

  void add_edge(int u, int v, T cap, T cost) {
    g.emplace_back(Edge{.v = v, .cap = cap, .cost = cost, .next = head[u]});
    head[u] = (int)g.size() - 1;
    g.emplace_back(Edge{.v = u, .cap = 0, .cost = -cost, .next = head[v]});
    head[v] = (int)g.size() - 1;
  }

  std::pair<T, T> mcmf(int s, int t) {  // <cost, flow>
    this->s = s;
    this->t = t;
    T cost = 0, flow = 0, f = 0;
    std::fill(d.begin(), d.end(), 0);
    while (true) {
      cur = head;
      while (f = aug(s, inf)) {
        flow += f;
        cost += f * d[s];
        std::fill(vis.begin(), vis.end(), false);
      }
      if (modlabel()) break;
    }
    return std::make_pair(cost, flow);
  }

 private:
  T aug(int u, T a) {
    if (u == t) return a;
    vis[u] = true;
    T flow = 0, f = 0;
    for (int &i = cur[u]; i != -1; i = g[i].next) {
      Edge &e = g[i];
      if (e.cap && !vis[e.v] && d[u] == d[e.v] + e.cost) {
        if (f = aug(e.v, std::min(a, e.cap))) {
          flow += f;
          e.cap -= f;
          g[i ^ 1].cap += f;
          a -= f;
          if (a == 0) break;
        }
      }
    }
    return flow;
  }

  bool modlabel() {
    T tmp = inf;
    for (int u = 0; u < n; ++u) if (vis[u]) {
      for (int i = head[u]; i != -1; i = g[i].next) {
        Edge &e = g[i];
        if (e.cap && !vis[e.v])
          tmp = min(tmp, d[e.v] + e.cost - d[u]);
      }
    }
    if (tmp == inf) return true;
    for (int u = 0; u < n; ++u) if (vis[u]) {
      vis[u] = false;
      d[u] += tmp;
    }
    return false;
  }
};

