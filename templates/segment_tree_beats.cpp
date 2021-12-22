// Support three type of operations:
// - Insert a value v at position p.
// - Set a[i] to min(a[i], v) for all i in [l, r].
// - Query the maxmimum element in [l, r].
struct SegmentTreeBeats {
 public:
  explicit SegmentTreeBeats(int n) : n(n), nodes(n << 1) {}

  void insert(int p, int v, int l, int r) {
    if (l == r) {
      Node& u = get_node(l, r);
      u.vmax = v;
      u.vmax_cnt = 1;
      return;
    }
    int mid = (l + r) >> 1;
    down(l, mid, r, get_node(l, r), get_node(l, mid), get_node(mid + 1, r));
    if (p <= mid) insert(p, v, l, mid);
    else insert(p, v, mid + 1, r);
    up(l, mid, r, get_node(l, r), get_node(l, mid), get_node(mid + 1, r));
  }

  // OnUpdate :: void(int before, int after, int cnt).
  template<typename OnUpdate>
  void update_min(int v, int l, int r, OnUpdate&& on_update) {
    Node& u = get_node(l, r);
    if (u.vmax <= v) return;
    if (u.submax < v) {
      on_update(u.vmax, v, u.vmax_cnt);
      u.update(v - u.vmax);
      return;
    }
    int mid = (l + r) >> 1;
    down(l, mid, r, get_node(l, r), get_node(l, mid), get_node(mid + 1, r));
    update_min(v, l, mid, std::forward<OnUpdate>(on_update));
    update_min(v, mid + 1, r, std::forward<OnUpdate>(on_update));
    up(l, mid, r, get_node(l, r), get_node(l, mid), get_node(mid + 1, r));
  }

  // OnUpdate :: void(int before, int after, int cnt).
  template<typename OnUpdate>
  void update_min(int L, int R, int v, int l, int r, OnUpdate&& on_update) {
    if (R < l || r < L || R < L) return;
    if (L <= l && r <= R) {
      update_min(v, l, r, std::forward<OnUpdate>(on_update));
      return;
    }
    int mid = (l + r) >> 1;
    down(l, mid, r, get_node(l, r), get_node(l, mid), get_node(mid + 1, r));
    update_min(L, R, v, l, mid, std::forward<OnUpdate>(on_update));
    update_min(L, R, v, mid + 1, r, std::forward<OnUpdate>(on_update));
    up(l, mid, r, get_node(l, r), get_node(l, mid), get_node(mid + 1, r));
  }

  int size() const { return n; }

  int query_max(int L, int R, int l, int r) {
    if (R < l || r < L || R < L) return -INF;
    if (L <= l && r <= R) return get_node(l, r).vmax;
    int mid = (l + r) >> 1;
    down(l, mid, r, get_node(l, r), get_node(l, mid), get_node(mid + 1, r));
    return std::max(query_max(L, R, l, mid), query_max(L, R, mid + 1, r));
  }

 private:
  static constexpr int INF = 0x3f3f3f3f;

  struct Node {
    int vmax = -INF;
    int vmax_cnt = 0;
    int submax = -INF;

    int tag = 0;

    void update(int dt) {
      if (dt) {
        vmax += dt;
        tag += dt;
      }
    }
  };

  Node& get_node(int l, int r) {
    return nodes[(l + r) | (l != r)];
  }

  void down(int l, int mid, int r, Node& u, Node& lu, Node& ru) {
    if (u.tag) {
      int x = lu.vmax;
      int y = ru.vmax;
      if (x >= y) lu.update(u.tag);
      if (x <= y) ru.update(u.tag);
      u.tag = 0;
    }
  }

  void up(int l, int mid, int r, Node& u, const Node& lu, const Node& ru) {
    if (lu.vmax > ru.vmax) {
      u.vmax = lu.vmax;
      u.vmax_cnt = lu.vmax_cnt;
      u.submax = std::max(lu.submax, ru.vmax);
    } else if (lu.vmax < ru.vmax) {
      u.vmax = ru.vmax;
      u.vmax_cnt = ru.vmax_cnt;
      u.submax = std::max(ru.submax, lu.vmax);
    } else {
      u.vmax = lu.vmax;
      u.vmax_cnt = lu.vmax_cnt + ru.vmax_cnt;
      u.submax = std::max(lu.submax, ru.submax);
    }
  }

  int n;
  std::vector<Node> nodes;
};

