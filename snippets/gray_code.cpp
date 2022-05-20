struct GrayCode {

  // Generate a cyclic permutation of {0, 1, .. , 2^n - 1},
  // so that any two neighbor elements diff in exactly one bit.
  static std::vector<int> generate(int n) {
    assert(n > 0);
    std::vector<int> cur{0, 1};
    for (int i = 1; i < n; ++i) {
      std::vector<int> nex = cur;
      for (int j = (int)cur.size() - 1; j >= 0; --j) {
        nex.emplace_back(cur[j] | 1 << i);
      }
      cur.swap(nex);
    }
    return cur;
  }

  template<typename T = int>
  static T next(T mask, int n) {
    assert(n > 0);
    if (mask == T(1) << (n - 1)) return 0;
    int parity = __builtin_parityll(mask);
    if (parity == 0) return mask ^ 1;
    return mask ^ (mask & -mask) << 1;
  }

  template<typename T = int>
  static T prev(T mask, int n) {
    assert(n > 0);
    if (mask == 0) return T(1) << (n - 1);
    int parity = __builtin_parityll(mask);
    if (parity == 1) return mask ^ 1;
    return mask ^ (mask & -mask) << 1;
  }
};

