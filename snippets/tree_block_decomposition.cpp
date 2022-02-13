#include <bits/stdc++.h>
#ifdef ALGO
#include "el_psy_congroo.hpp"
#else
#define DUMP(...) 1145141919810
#define CHECK(...) (__VA_ARGS__)
#endif

namespace {

template <typename T, typename U> inline void enlarge(T &a, U b) { if (a < b) a = b; }

using LL = long long;
const int kN = 100000 + 5;
const int MAGIC = 256;
const int NUM_MAGIC = (kN + MAGIC - 1) / MAGIC * 10;

struct Edge {
  int u, v;
};

std::string to_string(const Edge &e) {
  return std::string("Edge{") + std::to_string(e.u) + ", " +
         std::to_string(e.v) + "}";
}

template <typename T, typename U, int N> struct TreeT {
  T start[N + 1];
  U v[N << 1];
  T n;
  T m = 0;

  std::pair<T, U> tree_buffer[N << 1];

  void init(T n) {
    this->n = n;
    clear();
  }

  void clear() {
    memset(start, 0, sizeof(T) * (n + 1));
    m = 0;
  }

  void add_edge(T x, const U &y) {
    ++start[x];
    tree_buffer[m].first = x;
    tree_buffer[m++].second = y;
  }

  void make() {
    for (T i = 0; i < n; ++i) {
      start[i + 1] += start[i];
    }
    for (int i = 0; i < m; ++i) {
      v[--start[tree_buffer[i].first]] = tree_buffer[i].second;
    }
  }
};

using OriginalTree = TreeT<int, int, kN>;
using Tree = TreeT<int16_t, int16_t, MAGIC << 1>;

OriginalTree original_tree;

int n, m;

struct Borders {
  int a[2] = {-1, -1};

  int operator[](int index) const { return a[index]; }

  int size() const { return (a[0] != -1) + (a[1] != -1); }

  void recv(const Borders &other) {
    CHECK(a[1] == -1 && other.a[1] == -1);
    if (a[0] == -1)
      a[0] = other.a[0];
  }

  void emplace_back(int u) { a[a[0] != -1] = u; }

  bool empty() const { return a[0] == -1; }
};

struct Cluster {
  Borders borders;
  std::vector<Edge> E;
  int id = -1;

  bool can_merge_with(const Cluster &other) const {
    return borders.size() + other.borders.size() <= 1 &&
           (E.size() < MAGIC || E.size() + other.E.size() < 2 * MAGIC);
  }

  void recv(Cluster &other) {
    if (other.E.size() > E.size()) {
      std::swap(other.E, E);
    }
    borders.recv(std::move(other.borders));
    std::move(other.E.begin(), other.E.end(), std::back_inserter(E));
  }
};

void swap(Cluster &lhs, Cluster &rhs) {
  std::swap(lhs.borders, rhs.borders);
  std::swap(lhs.E, rhs.E);
  std::swap(lhs.id, rhs.id);
}

bool operator<(const Cluster &lhs, const Cluster &rhs) {
  if (lhs.borders.size() != rhs.borders.size()) {
    return lhs.borders.size() > rhs.borders.size();
  }
  return lhs.E.size() < rhs.E.size();
}

std::vector<Cluster> clusters;

void decompose(int u, int fa, const OriginalTree &tree) {
  static std::vector<Cluster> holded_clusters;
  int cnt_borders = 0;
  int h = holded_clusters.size();
  for (int i = tree.start[u]; i < tree.start[u + 1]; ++i) {
    int v = tree.v[i];
    if (v == fa)
      continue;
    decompose(v, u, tree);
    int hh = holded_clusters.size();
    cnt_borders += holded_clusters[hh - 1].borders.size();
    holded_clusters[hh - 1].E.emplace_back(Edge{.u = u, .v = v});
  }
  int hh = holded_clusters.size();
  if (h == hh) {
    holded_clusters.emplace_back();
    return;
  }
  {
    std::sort(holded_clusters.begin() + h, holded_clusters.begin() + hh);
    int ww = h;
    while (ww < hh && holded_clusters[ww].borders.size() == 1)
      ++ww;
    for (int i = ww, j = h; i < hh; ++i) {
      while (j < ww && !holded_clusters[j].can_merge_with(holded_clusters[i]))
        ++j;
      if (j < ww && holded_clusters[j].can_merge_with(holded_clusters[i])) {
        holded_clusters[j].recv(holded_clusters[i]);
      } else {
        holded_clusters[ww++] = holded_clusters[i];
      }
    }
    hh = ww;
    holded_clusters.resize(hh);
  }
  if (fa != -1 && cnt_borders <= 1 && hh <= h + 1 &&
      holded_clusters[hh - 1].E.size() < MAGIC) {
    CHECK(h + 1 == hh);
    return;
  }
  int keeped = -1;
  for (int i = h; i < hh; ++i) {
    Cluster &cluster = holded_clusters[i];
    if (cluster.borders.empty()) {
      if (fa != -1 && keeped == -1 && cluster.E.size() < MAGIC) {
        keeped = i;
      } else {
        cluster.borders.emplace_back(cluster.E[cluster.E.size() / 2].v);
      }
    }
    cluster.borders.emplace_back(u);
  }
  if (keeped != -1) {
    std::swap(holded_clusters[h], holded_clusters[keeped]);
    ++h;
  }
  std::move(holded_clusters.begin() + h, holded_clusters.end(),
            std::back_inserter(clusters));
  holded_clusters.resize(h);
  if (keeped == -1) {
    holded_clusters.emplace_back();
    holded_clusters.back().borders.emplace_back(u);
  }
}

struct Hash {
  int16_t table[kN];
  int relative_points[NUM_MAGIC];
  int16_t tot = 0;

  Hash() { memset(table, -1, sizeof(table)); }

  void put(int x) {
    if (table[x] == -1) {
      relative_points[tot] = x;
      table[x] = tot++;
    }
  }

  int hash(int x) const {
    CHECK(table[x] != -1);
    return table[x];
  }

  int hash_no_check(int x) const { return table[x]; }

  void clear() {
    for (int i = 0; i < tot; ++i)
      table[relative_points[i]] = -1;
    tot = 0;
  }
};

struct SparseTable {
  int u[18][kN << 1];
  int8_t lg[kN << 1];

  int *access() { return u[0]; }

  void build(int n) {
    lg[0] = -1;
    for (int i = 1; i < kN << 1; ++i)
      lg[i] = lg[i >> 1] + 1;
    for (int j = 1; (1 << j) <= n; ++j) {
      for (int i = 0; i + (1 << j) <= n; ++i) {
        u[j][i] = std::min(u[j - 1][i], u[j - 1][i + (1 << (j - 1))]);
      }
    }
  }

  int ask(int a, int b) const {
    CHECK(a <= b);
    int k = lg[b - a + 1];
    return std::min(u[k][a], u[k][b - (1 << k) + 1]);
  }
};

struct RmqLca {
  int n;
  int dfn[kN], rd[kN << 1], depth[kN];
  int stmp;
  SparseTable st;
  int *dr = st.access();

  void init(int size) {
    n = size;
    stmp = 0;
  }

  void build(const OriginalTree &tree) {
    this->dfs(0, -1, tree);
    st.build(stmp);
  }

  int get_lca_depth(int a, int b) const {
    if (dfn[a] > dfn[b])
      std::swap(a, b);
    return rd[st.ask(dfn[a], dfn[b])];
  }

  int get_dist(int a, int b) const {
    return depth[a] + depth[b] - (get_lca_depth(a, b) << 1);
  }

  void dfs(int u, int fa, const OriginalTree &tree) {
    depth[u] = fa == -1 ? 0 : depth[fa] + 1;
    dfn[u] = stmp;
    dr[stmp] = stmp;
    rd[stmp++] = depth[u];
    for (int i = tree.start[u]; i < tree.start[u + 1]; ++i) {
      int v = tree.v[i];
      if (v == fa)
        continue;
      this->dfs(v, u, tree);
      dr[stmp++] = dfn[u];
    }
  }
};

RmqLca lca_solver;

struct Query {
};

struct QueryContext {
  Query query;
  int id;
};

QueryContext query_contexts[kN];

struct ClusterContext {
};

ClusterContext cluster_context;

Hash border_hash;

void solve() {
  clusters.clear();
  decompose(0, -1, original_tree);
  for (int i = 0; i < clusters.size(); ++i) {
    clusters[i].id = i;
    CHECK(clusters[i].E.size() <= MAGIC * 2);
  }
  lca_solver.init(n);
  lca_solver.build(original_tree);
}

} // namespace

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::istream &reader = std::cin;

  while (reader >> n >> m) {
    for (int i = 0; i < n; ++i) {
      reader >> weight[i];
    }
    original_tree.init(n);
    for (int i = 0; i < n - 1; ++i) {
      int a, b;
      reader >> a >> b;
      --a;
      --b;
      original_tree.add_edge(a, b);
      original_tree.add_edge(b, a);
    }
    original_tree.make();

    solve();
  }
}
