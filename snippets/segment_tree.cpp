template<typename Node, typename Impl>
class SegmentTreeBase {
 public:
  explicit SegmentTreeBase(int n) : n(n), tree(n << 1) {}
  virtual ~SegmentTreeBase() = default;

  template<typename Handler>
  Handler traverse_all(Handler&& handler) {
    traverse_all(std::forward<Handler>(handler), 0, n - 1);
    return handler;
  }

  template<typename Handler>
  Handler traverse(Handler&& handler, int L, int R) {
    traverse(std::forward<Handler>(handler), L, R, 0, n - 1);
    return handler;
  }

  int size() const { return n; }

 protected:
  static int get_id(int l, int r) {
    return l + r | (l != r);
  }

  Node& get_node(int l, int r) { return tree[get_id(l, r)]; }

  // Handler() :: void operator () (int l, int r, Node& u).
  // Impl::down :: void down(int l, int mid, int r, Node& u, Node& lu, Node& ru).
  // Impl::up :: void up(int l, int mid, int r, Node& u, const Node& lu, const Node& ru).

 private:
  template<typename Handler>
  void traverse_all(Handler&& handler, int l, int r) {
    if (l == r) {
      handler(l, r, get_node(l, r));
      return;
    }
    int mid = (l + r) >> 1;
    static_cast<Impl*>(this)->down(l, mid, r, get_node(l, r), get_node(l, mid), get_node(mid + 1, r));
    traverse_all(std::forward<Handler>(handler), l, mid);
    traverse_all(std::forward<Handler>(handler), mid + 1, r);
    static_cast<Impl*>(this)->up(l, mid, r, get_node(l, r), get_node(l, mid), get_node(mid + 1, r));
  }

  template<typename Handler>
  void traverse(Handler&& handler, int L, int R, int l, int r) {
    if (R < l || r < L || L > R) return;
    if (L <= l && r <= R) {
      handler(l, r, get_node(l, r));
      return;
    }
    int mid = (l + r) >> 1;
    static_cast<Impl*>(this)->down(l, mid, r, get_node(l, r), get_node(l, mid), get_node(mid + 1, r));
    traverse(std::forward<Handler>(handler), L, R, l, mid);
    traverse(std::forward<Handler>(handler), L, R, mid + 1, r);
    static_cast<Impl*>(this)->up(l, mid, r, get_node(l, r), get_node(l, mid), get_node(mid + 1, r));
  }

  int n;
  std::vector<Node> tree;
};

struct Monoid {
  bool identity() const { return id_; }
  bool id_ = false;
  static Monoid make_identity() { Monoid ret; ret.id_ = true; return ret; }
};

Monoid operator*(const Monoid& lhs, const Monoid& rhs) {
  if (lhs.identity()) return rhs;
  if (rhs.identity()) return lhs;
  // TODO
}

struct Node {
  Monoid m;
};

struct SegmentTree : public SegmentTreeBase<Node, SegmentTree> {
  explicit SegmentTree(int n = 0) : SegmentTreeBase(n) {}
  virtual ~SegmentTree() = default;

  void down(int l, int mid, int r, Node& u, Node& lu, Node& ru) {
    // pass
  }

  void up(int l, int mid, int r, Node& u, const Node& lu, const Node& ru) {
    u.m = lu.m * ru.m;
  }

  void build() {
    traverse_all([&](int l, int r, Node& u) {
      assert(l == r);
    });
  }

  Monoid query(int L, int R) {
    Monoid ret = Monoid::make_identity();
    traverse([&](int l, int r, Node& u) {
      ret = ret * u.m;
    }, L, R);
    return ret;
  }

  Monoid query_all() { return get_node(0, size() - 1).m; }
};

