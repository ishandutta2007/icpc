template<typename T>
struct CostFlow {
 public:
  const T inf = std::numeric_limits<T>::max();
  int n = 0;
  int s = -1, t = -1;
  std::vector<int> head, prevv, preve;
  T dis;

  struct Edge {
    int v;
    T cap, cost;
    int next;
  };
  std::vector<Edge> g;

  CostFlow() = default;
  explicit CostFlow(int n) : n(n), head(n, -1), prevv(n), preve(n), dis(n, inf) {}

  void add_edge(int u, int v, T cap, T cost) {
    g.emplace_back(Edge{.v = v, .cap = cap, .cost = cost, .next = head[u]});
    head[u] = (int)g.size() - 1;
    g.emplace_back(Edge{.v = u, .cap = 0, .cost = -cost, .next = head[v]});
    head[v] = (int)g.size() - 1;
  }

  std::pair<T, T> mcmf(int s, int t) {  // <flow, cost>
    this->s = s;
    this->t = t;
    T flow = 0, cost = 0;
    while (true) {
      spfa(s);
      if (dis[t] == inf) break;
      T f = inf;
      for (int u = t; u != s; u = prevv[u])
        f = std::min(f, g[preve[u]].cap);
      cost += f * dis[t];
      flow += f;
      for (int u = t; u != s; u = prevv[u])
        g[preve[u]].cap -= f, g[preve[u] ^ 1].cap += f;
    }
  }

 private:
  void spfa(int source) {
    std::vector<bool> inq(n);
    std::queue<int> que;
    std::fill(dis.begin(), dis.end(), inf);
    dis[source] = 0;
    que.emplace(source);
    while (!que.empty()) {
      int u = que.front(); inq[u] = false; que.pop();
      for (int i = head[u]; i != -1; i = g[i].next) {
        Edge &e = g[i];
        if (e.cap && dis[e.v] > dis[u] + e.cost) {
          dis[e.v] = dis[u] + e.cost;
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

