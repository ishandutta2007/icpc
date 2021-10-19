#include <bits/stdc++.h>
#ifdef ALGO
#include "el_psy_congroo.hpp"
#else
#define DUMP(...) 1145141919810
#define CHECK(...) (__VA_ARGS__)
#endif

namespace {

struct Edge {
  int v;
  Edge(int v) : v(v) {}
};

struct HeavyLightDecomposition {
  explicit HeavyLightDecomposition(int n) : n(n), graph(n), header(n), dfn(n), rd(n), parent(n), depth(n), sz(n) {}

  int n = 0;
  std::vector<std::vector<Edge>> graph;
  std::vector<int> header, dfn, rd, parent, depth, sz;
  int tim = 0;

  void get_sz(int u, int fa) {
    sz[u] = 1;
    for (const Edge& e : graph[u]) {
      int v = e.v;
      if (v == fa) continue;
      get_sz(v,u);
      sz[u] += sz[v];
    }
  }

  void rebuild(int u, int fa, int color) {
    rd[tim] = u;
    dfn[u] = tim ++;
    parent[u] = fa;
    depth[u] = fa == -1 ? 0 : depth[fa] + 1;
    header[u] = color;
    int p = -1;
    for (const Edge& e : graph[u]) {
      int v = e.v;
      if (v == fa) continue;
      if (p == -1 || sz[v] > sz[p]) {
        p = v;
      }
    }
    if (p != -1) {
      rebuild(p,u,color);
    }
    for (const Edge& e : graph[u]) {
      int v = e.v;
      if (v == fa || v == p) continue;
      rebuild(v,u,v);
    }
  }

  int get_lca(int a, int b) {
    int ret = a;
    traverse([&ret, this](int side, int L, int R) {
      ret = this->rd[L];
    }, a, b);
    return ret;
  }

  // Handler() :: void operator () (int side, int L, int R).
  template<typename Handler>
  Handler traverse(Handler&& handler, int a, int b) {
    while (header[a] != header[b]) {
      if (depth[header[a]] > depth[header[b]]) {
        handler(0, dfn[header[a]], dfn[a]);
        a = parent[header[a]];
      } else {
        handler(1, dfn[header[b]], dfn[b]);
        b = parent[header[b]];
      }
    }
    if (dfn[a] < dfn[b]) {
      handler(1, dfn[a], dfn[b]);
    } else {
      handler(0, dfn[b], dfn[a]);
    }
    return handler;
  }
};

template<typename Node, typename Impl>
class SegmentTreeBase {
 public:
  explicit SegmentTreeBase(int n) : n(n), tree(n << 1) {}
  virtual ~SegmentTreeBase() = default;

  static int get_id(int l, int r) {
    return l + r | (l != r);
  }

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

 private:
  Node& get_node(int l, int r) { return tree[get_id(l, r)]; }

  // Handler() :: void operator () (int l, int r, Node& u).
  // Impl::down :: void down(int l, int mid, int r, Node& u, Node& lu, Node& ru).
  // Impl::up :: void up(int l, int mid, int r, Node& u, const Node& lu, const Node& ru).

  template<typename Handler>
  void traverse_all(Handler&& handler, int l, int r) {
    if (l == r) {
      handler(l, r, get_node(l, r));
      return;
    }
    int mid = (l + r) >> 1;
    traverse_all(std::forward<Handler>(handler), l, mid);
    traverse_all(std::forward<Handler>(handler), mid + 1, r);
    Impl::up(l, mid, r, get_node(l, r), get_node(l, mid), get_node(mid + 1, r));
  }

  template<typename Handler>
  void traverse(Handler&& handler, int L, int R, int l, int r) {
    if (R < l || r < L || L > R) return;
    if (L <= l && r <= R) {
      handler(l, r, get_node(l, r));
      return;
    }
    int mid = (l + r) >> 1;
    Impl::down(l, mid, r, get_node(l, r), get_node(l, mid), get_node(mid + 1, r));
    traverse(std::forward<Handler>(handler), L, R, l, mid);
    traverse(std::forward<Handler>(handler), L, R, mid + 1, r);
    Impl::up(l, mid, r, get_node(l, r), get_node(l, mid), get_node(mid + 1, r));
  }

  int n;
  std::vector<Node> tree;
};

struct Monoid {
  int left = -1, right = -1, cnt = 0;

  bool id() const { return left == -1; }

  Monoid reverse() const {
    return Monoid{.left = right, .right = left, .cnt = cnt};
  }
};

Monoid operator * (const Monoid& lhs, const Monoid& rhs) {
  if (lhs.id()) return rhs;
  if (rhs.id()) return lhs;
  return Monoid{lhs.left, rhs.right, lhs.cnt + rhs.cnt + (lhs.right == rhs.left)};
}

struct Node {
  Monoid m;
  int lazy = -1;

  void draw(int l, int r, int c) {
    lazy = c;
    m = Monoid{.left = c, .right = c, .cnt = r - l};
  }
};

struct SegmentTree : public SegmentTreeBase<Node, SegmentTree> {
  explicit SegmentTree(int n) : SegmentTreeBase(n) {}
  virtual ~SegmentTree() = default;

  static void down(int l, int mid, int r, Node& u, Node& lu, Node& ru) {
    if (u.lazy == -1) return;
    lu.draw(l, mid, u.lazy);
    ru.draw(mid + 1, r, u.lazy);
    u.lazy = -1;
  }

  static void up(int l, int mid, int r, Node& u, const Node& lu, const Node& ru) {
    u.lazy = -1;
    u.m = lu.m * ru.m;
  }

  void build() {
    traverse_all([](int l, int r, Node& u) {
      u.lazy = -1;
      u.m = Monoid{.left = l, .right = r, .cnt = r - l};
    });
  }

  Monoid query(int L, int R) {
    Monoid ret;
    traverse([&ret](int l, int r, Node& u) {
      ret = ret * u.m;
    }, L, R);
    return ret;
  }

  void update(int L, int R, int c) {
    traverse([c](int l, int r, Node& u) {
      u.draw(l, r, c);
    }, L, R);
  }
};

void update(HeavyLightDecomposition& hld, SegmentTree& sgt, int x, int y, int color) {
  hld.traverse([&sgt, color](int side, int L, int R) {
    sgt.update(L, R, color);
  }, x, y);
}

Monoid query(HeavyLightDecomposition& hld, SegmentTree& sgt, int x, int y) {
  Monoid mx, my;
  hld.traverse([&mx, &my, &sgt](int side, int L, int R) {
    if (side == 0) {
      mx = sgt.query(L, R) * mx;
    } else {
      my = sgt.query(L, R) * my;
    }
  }, x, y);
  return mx.reverse() * my;
}

}  // namespace

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::istream& reader = std::cin;

  int cas;
  reader >> cas;
  while (cas--) {
    int n, m;
    reader >> n >> m;
    HeavyLightDecomposition hld(n);
    for (int i = 0; i + 1 < n; ++i) {
      int x, y;
      reader >> x >> y; --x; --y;
      hld.graph[x].emplace_back(y);
      hld.graph[y].emplace_back(x);
    }
    hld.get_sz(0, -1);
    hld.rebuild(0, -1, 0);
    SegmentTree sgt(n);
    sgt.build();
    for (int i = 0; i < m; ++i) {
      int op, x, y;
      reader >> op >> x >> y; --x; --y;
      if (op == 1) {
        update(hld, sgt, x, y, n + i);
      } else {
        printf("%d\n", query(hld, sgt, x, y).cnt);
      }
    }
  }
}

