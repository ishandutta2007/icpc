template<typename T>
std::pair<T, std::vector<int>> km(int n, int m, const std::vector<std::vector<T>>& adj) {
  // Returns the MINIMUM perfect matching.
  // Index: 1..n, 1..m
  const T inf = std::numeric_limits<T>::max();
  std::vector<T> u(n + 1), v(m + 1);
  std::vector<int> p(m + 1), way(m + 1);
  for (int i = 1; i <= n; ++ i) {
    p[0] = i;
    int j0 = 0;
    std::vector<T> minv(m + 1, inf);
    std::vector<bool> used(m + 1,false);
    do {
      used[j0] = true;
      int i0 = p[j0], j1;
      T delta = inf;
      for (int j = 1; j <= m; ++ j)
        if (!used[j] && adj[i0][j] != inf) {
          T cur = adj[i0][j] - u[i0] - v[j];
          if (cur < minv[j])
            minv[j] = cur, way[j] = j0;
          if (minv[j] < delta)
            delta = minv[j], j1 = j;
        }
      for (int j = 0; j <= m; ++j)
        if (used[j])
          u[p[j]] += delta, v[j] -= delta;
        else
          minv[j] -= delta;
      j0 = j1;
    } while (p[j0] != 0);
    do {
      int j1 = way[j0];
      p[j0] = p[j1];
      j0 = j1;
    } while (j0);
  }
  return std::make_pair(-v[0], p);
}

