struct DirectedMinimumSpanningTree {
 public:
  void add_edge(int u, int v, int cost, int id) {
    g.emplace_back(Edge{.u = u, .v = v, .c = create_cost(cost, id), .from = u, .to = v, .val = cost});
  }

  int solve(int root, int n, std::vector<int>* path = nullptr) {
    int m = g.size();
    std::vector<int> vis(n);
    std::vector<Cost*> least(n);
    std::vector<int> in(n);  // pre
    std::vector<int> idx(n);

    int ret = 0;
    while(true) {
      int i, j, k, cnt, id;
      vis.resize(n);
      least.assign(n, nullptr);
      in.assign(n, -1);
      idx.resize(n);
      for(i = 0; i < m; ++i) {
        int u = g[i].u;
        int v = g[i].v;
        if(u != v && cmp(g[i].c, least[v])) {
          least[v] = g[i].c;
          in[v] = u;
        }
      }
      for(i = 0; i < n; ++i) if(i != root && in[i] == -1) return -1;
      std::fill(vis.begin(), vis.end(), -1);
      std::fill(idx.begin(), idx.end(), -1);
      for(i = cnt = id = 0, in[root] = -1; i < n; ++i) if(i != root) {
        ret += least[i]->c;
        least[i]->use();
        if(~vis[i]) continue;
        for(j = i, k = -1; ; j = in[j]) {
          if(~vis[j]) {
            if(vis[j] == cnt) k = j;
            break;
          }
          vis[j] = cnt;
        }
        if(~k) {
          for(j = in[k]; j != k; j = in[j]) idx[j] = id;
          idx[k] = id++;
        }
        ++cnt;
      }
      if(!id) break;
      // Relabeling.
      for(i = 0; i < n; ++i) if(idx[i] == -1) idx[i] = id++;
      for(i = 0; i < m; ++i) {
        int v = g[i].v;
        g[i].u = idx[g[i].u];
        g[i].v = idx[g[i].v];
        if(g[i].u != g[i].v)
          g[i].c = create_cost(g[i].c, least[v]);
      }
      n = id;
      root = idx[root];
    }
    if (path != nullptr) {
      path->clear();
      for(int i = (int)cov.size() - 1; i >= 0; --i) cov[i]->push();
      for(int i = 0; i < cov.size(); ++i) {
        Cost* c = cov[i];
        if(c->id != -1 && c->c > 0 && c->used > 0) path->push_back(c->id);
      }
      sort(path->begin(), path->end());
    }
    return ret;
  }

 private:
  struct Cost {
    int c, id;
    int used = 0;
    Cost* a = nullptr;
    Cost* b = nullptr;  // c = a - b;

    Cost(int c, int id) : c(c), id(id), a(nullptr), b(nullptr) {}
    Cost(Cost* a, Cost* b) : a(a), b(b), c(a->c - b->c), id(-1) {}

    bool operator < (const Cost& t) const { return c < t.c; }
    void push() {
      if(id == -1) {
        a->used += used;
        b->used -= used;
      }
    }

    void use() { ++used; }
  };

  Cost* create_cost(int c, int id) {
    cov_storage.emplace_back(new Cost(c, id));
    cov.emplace_back(cov_storage.back().get());
    return cov.back();
  }

  Cost* create_cost(Cost* a, Cost* b) {
    cov_storage.emplace_back(new Cost(a, b));
    cov.emplace_back(cov_storage.back().get());
    return cov.back();
  }

  bool cmp(Cost* a, Cost* b) const {  // a < b
    if(a == 0 || b == 0) return b == 0;
    else return a->c < b->c;
  }

  bool better(Cost* a, Cost* b) const {  // a better than b
    if (a == 0 || b == 0) return b == 0;
    return a->c < b->c;
  }

  struct Edge {
    int u, v;
    Cost* c = nullptr;
    int from, to, val;
  };

  std::vector<Edge> g;
  std::vector<Cost*> cov;
  std::vector<std::unique_ptr<Cost>> cov_storage;
};

