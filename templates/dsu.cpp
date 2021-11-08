struct Dsu {
  int n;
  std::vector<int> dsu;

  Dsu() = default;

  explicit Dsu(int n) : n(n), dsu(n) {
    std::iota(dsu.begin(), dsu.end(), 0);
  }

  int find(int x) {
    return dsu[x] == x ? x : dsu[x] = find(dsu[x]);
  }

  bool same(int x, int y) {
    x = find(x);
    y = find(y);
    return x == y;
  }

  bool merge(int x, int y) {
    x = find(x);
    y = find(y);
    if (x == y) return false;
    dsu[y] = x;
    return true;
  }
};

