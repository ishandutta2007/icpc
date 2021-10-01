template<typename EdgeT>
struct CartesianTree {
  int n = 0;
  std::vector<std::vector<EdgeT>> graph;
  int root = -1;

  explicit CartesianTree(const std::vector<int>& a) : n(a.size()), graph(n) {
    if (n == 0) return;
    std::vector<int> stack;
    for (int i = 0; i < n; ++i) {
      int last = -1;
      while (!stack.empty() && a[stack.back()] > a[i]) {
        int v = stack.back(); stack.pop_back();
        if (last != -1) {
          graph[v].emplace_back(last);
        }
        last = v;
      }
      if (last != -1) {
        graph[i].emplace_back(last);
      }
      stack.emplace_back(i);
    }
    for (int i = 0; i + 1 < stack.size(); ++i) {
      graph[stack[i]].emplace_back(stack[i + 1]);
    }
    root = stack[0];
  }
};
