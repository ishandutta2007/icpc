struct RevertableDsu {
 public:
  std::vector<int> dsu;
  std::vector<int> sz;

  explicit RevertableDsu(int n) : dsu(n), sz(n, 1) {
    std::iota(dsu.begin(), dsu.end(), 0);
  }

  bool same(int x, int y) {
    x = find(x);
    y = find(y);
    return x == y;
  }

  int find(int x) {
    while (x != dsu[x]) x = dsu[x];
    return x;
  }

  bool merge(int x, int y) {
    x = find(x);
    y = find(y);
    if (x == y) return false;
    if (sz[x] < sz[y]) std::swap(x, y);
    modify(sz[x], sz[x] + sz[y]);
    modify(dsu[y], x);
    return true;
  }

  int get_history_size() const { return history.size(); }

  void revert(int h) {
    while (history.size() > h) {
      history.back().first = history.back().second;
      history.pop_back();
    }
  }

 private:
  void modify(int& a, int b) {
    history.emplace_back(a, a);
    a = b;
  }

  std::vector<std::pair<int&, int>> history;
};

