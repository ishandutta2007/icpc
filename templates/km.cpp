template<typename T>
struct KuhnMunkres {
  static constexpr T inf = std::numeric_limits<T>::max();
  int n = 0, m = 0;
  std::vector<int> lv, rv, left;
  std::vector<std::vector<T>> adj;
  std::vector<T> la, ra;

  KuhnMunkres(int n, int m) : n(n), m(m), lv(n), rv(m), left(m), adj(n, std::vector<T>(m, -inf)), la(n), ra(m) {}

  bool expath(int u) {
    lv[u] = 1;
    for (int i = 0; i < m; ++i)
      if (!rv[i] && la[u] + ra[i] == adj[u][i]) {
        rv[i] = 1;
        if (left[i] == -1 || expath(left[i]))
          return left[i] = u, true;
      }
    return false;
  }

  T km(int n, int m) {
    assert(this->n >= n);
    assert(this->m >= m);
    this->n = n;
    this->m = m;
    std::fill(left.begin(), left.end(), -1);
    for (int i = 0; i < n; ++i) {
      la[i] = -inf;
      for (int j = 0; j < m; ++j) la[i] = std::max(la[i], adj[i][j]);
    }
    for (int i = 0; i < m; ++i) ra[i] = 0;
    for (int u = 0; u < n; ++u) {
      for (int i = 0; i < n; ++i) lv[i] = 0;
      for (int i = 0; i < m; ++i) rv[i] = 0;
      while (!expath(u)) {
        T d = inf;
        for (int i = 0; i < n; ++i) if (lv[i])
          for (int j = 0; j < m; ++j) if (!rv[j])
            d = std::min(d, la[i] + ra[j] - adj[i][j]);
        for (int i = 0; i < n; ++i) if (lv[i]) la[i] -= d, lv[i] = 0;
        for (int i = 0; i < m; ++i) if (rv[i]) ra[i] += d, rv[i] = 0;
      }
    }
    T ret = 0;
    for (int i = 0; i < m; ++i) if (left[i] != -1) ret += adj[left[i]][i];
    return ret;
  }
};

