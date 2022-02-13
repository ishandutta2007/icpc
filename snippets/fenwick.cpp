template<typename T>
struct Fenwick {
  std::vector<T> bits;

  explicit Fenwick(int n = 0) : bits(n) {}

  void update(int p, T dt) {
    for (int i = p; i < bits.size(); i += ~i & i + 1) bits[i] += dt;
  }

  T query(int p) const {
    T ret{};
    for (int i = p; i >= 0; i -= ~i & i + 1) ret += bits[i];
    return ret;
  }

  T kth(T k) const {
    int p = -1;
    int highest_bit = 0;
    for (int x = bits.size(); x; x >>= 1, ++highest_bit);
    for (int b = highest_bit; b >= 0; --b) {
      p += 1 << b;
      if (p >= bits.size() || bits[p] >= k) p -= 1 << b;
      else k -= bits[p];
    }
    return p + 1 >= bits.size() ? -1 : p + 1;
  }
};

