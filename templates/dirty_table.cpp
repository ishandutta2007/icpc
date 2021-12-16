template<typename T>
struct DirtyTable {
 public:
  DirtyTable() = default;
  DirtyTable(int n, T default_value = T(0)) : table(n, default_value), vis(n, 0) {}

  void clear() { ++stmp; }
  T get(int p) const { return vis[p] == stmp ? table[p] : default_value; }
  bool contains(int p) const { return vis[p] == stmp; }
  void set(int p, T val) { table[p] = val; vis[p] = stmp; }
  void plus_one(int p) { set(p, get(p) + 1); }
  void minus_one(int p) { set(p, get(p) - 1); }

  bool minify(int p, T val) {
    if (vis[p] != stmp) {
      set(p, val);
      return true;
    } else if (table[p] > val) {
      table[p] = val;
      return true;
    }
    return false;
  }

  bool enlarge(int p, T val) {
    if (vis[p] != stmp) {
      set(p, val);
      return true;
    } else if (table[p] < val) {
      table[p] = val;
      return true;
    }
    return false;
  }

 private:
  int stmp = 1;
  std::vector<T> table;
  std::vector<int> vis;
  T default_value = 0;
};

