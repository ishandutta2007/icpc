template<typename Edge>
struct VirtualGraph {
  const std::vector<int>& dfn;

  int n;
  std::vector<std::vector<Edge>> graph;
  std::vector<int> original_points;
  std::vector<int> point_weight;

  // Prerequirements of get_index:
  // - points are sorted in dfn increasing order.
  // - u is inside points.
  static int get_index(const std::vector<int>& dfn, const std::vector<int>& points, int u) {
    const int index = std::lower_bound(points.begin(), points.end(), u, [&](int x, int y) {
      return dfn[x] < dfn[y];
    }) - points.begin();
    CHECK(index >= 0 && index < points.size());
    return index;
  }

  // Construct a virtual tree from given points.
  template<typename GetLca, typename GetPointWeight, typename GetEdgeWeight>
  explicit VirtualGraph(const std::vector<int>& dfn,
                        std::vector<int> points,
                        GetLca&& get_lca,
                        GetPointWeight&& get_point_weight,
                        GetEdgeWeight&& get_edge_weight) : dfn(dfn) {
    std::sort(points.begin(), points.end(), [&](int x, int y) {
      return dfn[x] < dfn[y];
    });
    points.erase(std::unique(points.begin(), points.end()), points.end());
    for (int i = (int)points.size() - 1; i > 0; --i) {
      points.emplace_back(get_lca(points[i], points[i - 1]));
    }
    std::sort(points.begin(), points.end(), [&](int x, int y) {
      return dfn[x] < dfn[y];
    });
    points.erase(std::unique(points.begin(), points.end()), points.end());

    original_points = points;
    n = original_points.size();
    graph.resize(n);
    point_weight.resize(n);

    for (int i = 0; i < points.size(); ++i) {
      point_weight[i] = get_point_weight(points[i]);
    }

    for (int i = (int)points.size() - 1; i > 0; --i) {
      int u = original_points[i];
      int v = original_points[i - 1];
      int lca = get_lca(u, v);
      int ew = get_edge_weight(u, lca);
      graph[get_index(dfn, original_points, lca)].emplace_back(i, ew);
    }
  }

  int get_index(int x) const { return get_index(dfn, original_points, x); }
  int size() const { return n; }
};

/*
  VirtualGraph vgraph(
      hld.dfn,
      points,
      [&hld](int x, int y) -> int { return hld.get_lca(x, y); },
      [&scc](int x) -> int { return scc.cardinality[x]; },
      [&hld](int x, int lca) -> int {
        return hld.depth[x] - hld.depth[lca] - 1;
      });
*/

