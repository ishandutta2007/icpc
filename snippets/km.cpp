template<typename T>
struct KuhnMunkres {
  static constexpr T inf = std::numeric_limits<T>::max();
  int n = 0, m = 0;
  std::vector<int> lv, rv, left, right;
  std::vector<std::vector<T>> adj;
  std::vector<T> la, ra;
  std::vector<T> slack;
  std::vector<int> pre;

  KuhnMunkres() = default;
  KuhnMunkres(int n, int m) : n(n), m(m), lv(n), rv(m), left(m, -1), right(n, -1), adj(n, std::vector<T>(m, -inf)), la(n), ra(m), slack(m), pre(m, -1) {}

  void modify(int u) {
    for (int v = u, last; v != -1; v = last) {
      last = right[pre[v]];
      right[pre[v]] = v;
      left[v] = pre[v];
    }
  }

  void aug(int start) {
    for (int i = 0; i < n; ++i) lv[i] = 0;
    for (int i = 0; i < m; ++i) rv[i] = 0;
    for (int i = 0; i < m; ++i) slack[i] = inf;
    for (int i = 0; i < m; ++i) pre[i] = -1;
    std::queue<int> que;
    que.emplace(start);
    while (true) {
      while (!que.empty()) {
        int u = que.front(); que.pop();
        lv[u] = 1;
        for (int v = 0; v < m; ++v) {
          if (rv[v] || adj[u][v] == -inf) continue;
          T delta = la[u] + ra[v] - adj[u][v];
          if (delta < slack[v]) {
            slack[v] = delta;
            pre[v] = u;
            if (!delta) {
              rv[v] = 1;
              if (left[v] == -1) {
                modify(v);
                return;
              }
              que.emplace(left[v]);
            }
          }
        }
      }
      T delta = inf;
      for (int i = 0; i < m; ++i) if (!rv[i]) delta = std::min(delta, slack[i]);
      for (int i = 0; i < n; ++i) if (lv[i]) la[i] -= delta;
      for (int i = 0; i < m; ++i) {
        if (rv[i]) ra[i] += delta; else slack[i] -= delta;
      }
      for (int i = 0; i < m; ++i) {
        if (!rv[i] && !slack[i]) {
          rv[i] = 1;
          if (left[i] == -1) {
            modify(i);
            return;
          }
          que.emplace(left[i]);
        }
      }
    }
  }

  T km() {
    for (int i = 0; i < n; ++i) {
      la[i] = -inf;
      for (int j = 0; j < m; ++j) la[i] = std::max(la[i], adj[i][j]);
    }
    for (int i = 0; i < m; ++i) ra[i] = 0;
    for (int i = 0; i < n; ++i) aug(i);
    T ret = 0;
    for (int i = 0; i < m; ++i) {
      assert(left[i] != -1);
      ret += adj[left[i]][i];
    }
    return ret;
  }
};

