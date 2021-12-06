// Find two spanning trees without any common edge.
// Matroid intersection algorithm.
struct TwoDisjointSpanningTrees {
 public:
  explicit TwoDisjointSpanningTrees(int n, int m) : n(n), m(m), head(n, -1), e(2), mark(n, false), prev(n), preu(n), last(m << 1), ch(m, -1) {}

  bool solve(const std::vector<std::pair<int, int>>& input_edges) {
    assert(input_edges.size() == m);
    int cnt = 0;
    for (int i = 0; i < m; ++i) {
      add_edge(input_edges[i].first, input_edges[i].second);
      cnt += bfs(i);
    }
    return cnt == ((n - 1) << 1);
  }

 private:
  void add_edge(int u, int v) {
    g.emplace_back(Edge{.v = v, .next = head[u]});
    head[u] = (int)g.size() - 1;
    g.emplace_back(Edge{.v = u, .next = head[v]});
    head[v] = (int)g.size() - 1;
    e[0].emplace_back(u);
    e[1].emplace_back(v);
  }

  bool find_cycle(int flag, int x, int p) {
    if (x == p) return true;
    for (int i = head[x]; i != -1; i = g[i].next) {
      int v = g[i].v;
      if (ch[i >> 1] == flag && !mark[v]) {
        mark[v] = true;
        prev[v] = i >> 1 << 1 | flag;
        preu[v] = x;
        if (find_cycle(flag, v, p)) return true;
      }
    }
    return false;
  }

  bool bfs(int ip) {
    int qf, qe, q = 0;
    std::vector<int> que(m << 1);
    std::vector<bool> inq(m << 1, false);
    que[q++] = ip << 1;
    que[q++] = ip << 1 | 1;
    inq[ip << 1] = true;
    inq[ip << 1 | 1] = true;
    qf = 0;
    qe = q;
    while (qf != qe) {
      while (qf != qe) {
        int c = que[qf++];
        std::fill(mark.begin(), mark.end(), false);
        mark[e[0][c >> 1]] = true;
        if (!find_cycle(c & 1, e[0][c >> 1], e[1][c >> 1])) {
          while ((c >> 1) != ip) {
            ch[c >> 1] ^= 1;
            c = last[c];
          }
          ch[ip] = c & 1;
          return true;
        }
        for (int i = e[1][c >> 1]; i != e[0][c >> 1]; i = preu[i]) {
          int j = prev[i] ^ 1;
          if (!inq[j]) {
            inq[j] = true;
            que[q++] = j;
            last[j] = c;
          }
        }
      }
      qe = q;
    }
    return false;
  }

  int n, m;
  std::vector<int> head;
  std::vector<std::vector<int>> e;
  std::vector<bool> mark;
  std::vector<int> prev, preu;
  std::vector<int> last;
  std::vector<int> ch;

  struct Edge {
    int v, next;
  };
  std::vector<Edge> g;
};

