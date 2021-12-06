struct BinaryLiftLCA {
 public:
  struct Input {
    int* parent = nullptr;
    int* dist = nullptr;
  };

  void init(int size, const Input& input) {
    init(size, input.parent, input.dist);
  }

  void init(int size, const int* parent, const int* dist) {
    int L = 1;
    while ((1 << L) < size) ++L;
    pjump.resize(L, std::vector<int>(size, -1));
    std::vector<int>(parent, parent + size).swap(pjump[0]);
    std::vector<int>(dist, dist + size).swap(depth);
    for (int i = 0; i + 1 < L; ++i)
      for (int u = 0; u < size; ++u)
        pjump[i + 1][u] = pjump[i][u] == -1 ? -1 : pjump[i][pjump[i][u]];
  }

  int get_lca(int a, int b) const {
    if (depth[a] < depth[b]) std::swap(a, b);
    for (int i = (int)pjump.size() - 1; i >= 0; --i)
      if ((depth[a] - depth[b]) >> i & 1)
        a = pjump[i][a];
    if (a == b) return a;
    for (int i = (int)pjump.size() - 1; i >= 0; --i)
      if (pjump[i][a] != pjump[i][b])
        a = pjump[i][a], b = pjump[i][b];
    return pjump[0][a];
  }
  int get_dist(int a, int b) const { return depth[a] + depth[b] - 2 * depth[get_lca(a, b)]; }
  int jump(int a, int step) const {
    if (step >= (1 << pjump.size())) return -1;
    for (int i = (int)pjump.size() - 1; i >= 0; --i)
      if (step >> i & 1)
        a = pjump[i][a];
    return a;
  }
  int walk(int a, int b, int step) const {
    int lca = get_lca(a, b);
    if (depth[a] - depth[lca] < step) {
      step = depth[a] + depth[b] - 2 * depth[lca] - step;
      std::swap(a, b);
    }
    return jump(a, step);
  }

 private:
  std::vector<std::vector<int>> pjump;
  std::vector<int> depth;
};

