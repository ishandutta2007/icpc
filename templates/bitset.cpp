struct Bitset {
 public:
  Bitset() = default;
  explicit Bitset(int n) : n(n), buckets(get_bucket_size(n)) { assert(n > 0); }

  void flip(int p) { assert(in_range(p)); buckets[p >> 6] ^= 1ULL << (p & 63); }
  void flip() { for (int i = 0; i < buckets.size(); ++i) buckets[i] ^= -1ULL; align_last_bucket(); }
  void set(int p) { assert(in_range(p)); buckets[p >> 6] |= 1ULL << (p & 63); }
  void set(int p, bool v) { if (v) set(p); else if (test(p)) flip(p); }
  void reset() { for (int i = 0; i < buckets.size(); ++i) buckets[i] = 0; }
  void resize(int m) { assert(m > 0); buckets.resize(get_bucket_size(m), 0); if (m < n) align_last_bucket_of(m); n = m; }

  bool test(int p) const { assert(in_range(p)); return buckets[p >> 6] >> (p & 63) & 1; }
  bool operator [] (int p) const { return test(p); }
  bool all() const {
    for (int i = 0; i + 1 < buckets.size(); ++i) {
      if (~buckets[i]) return false;
    }
    const ULL last = (n & 63) ? (1ULL << (n & 63)) - 1 : -1ULL;
    return buckets.back() == last;
  }
  bool any() const { for (ULL mask : buckets) if (mask) return true; return false; }
  bool none() const { return !any(); }

  int count() const { int ret = 0; for (ULL mask : buckets) ret += __builtin_popcountll(mask); return ret; }
  int size() const { return n; }
  int lowbit() const {
    for (int i = 0; i < buckets.size(); ++i) if (buckets[i]) return (i << 6) + lowbit(buckets[i]);
    return -1;
  }

  Bitset& operator&=(const Bitset& other) {
    resize(std::max(size(), other.size()));
    int m = other.size();
    for (int i = ((m - 1) >> 6) + 1; i < (int)buckets.size(); ++i) buckets[i] = 0;
    for (int i = (m - 1) >> 6; i >= 0; --i) buckets[i] &= other.buckets[i];
    return *this;
  }
  Bitset operator&(const Bitset& other) const { Bitset ret = *this; return ret &= other; }

  Bitset& operator|=(const Bitset& other) {
    resize(std::max(size(), other.size()));
    for (int i = 0; i < other.buckets.size(); ++i) buckets[i] |= other.buckets[i];
    return *this;
  }
  Bitset operator|(const Bitset& other) const { Bitset ret = *this; return ret |= other; }

  Bitset operator^=(const Bitset& other) {
    resize(std::max(size(), other.size()));
    for (int i = 0; i < other.buckets.size(); ++i) buckets[i] ^= other.buckets[i];
    return *this;
  }
  Bitset operator^(const Bitset& other) const { Bitset ret = *this; return ret ^= other; }
  Bitset operator~() const { Bitset ret = *this; ret.flip(); return ret; }
  Bitset& operator>>=(int m) {
    assert(m >= 0);
    int p = m >> 6;
    int w = m & 63;
    for (int i = 0; i < buckets.size(); ++i) {
      ULL a = i + p < buckets.size() ? buckets[i + p] >> w : 0;
      ULL b = w && i + p + 1 < buckets.size() ? buckets[i + p + 1] << (64 - w) : 0;
      buckets[i] = a | b;
    }
    return *this;
  }
  Bitset operator>>(int m) const { Bitset ret = *this; return ret >>= m; }
  Bitset& operator<<=(int m) {
    assert(m >= 0);
    int p = m >> 6;
    int w = m & 63;
    for (int i = (int)buckets.size() - 1; i >= 0; --i) {
      if (w == 0) {
        buckets[i] = i - p >= 0 ? buckets[i - p] : 0;
      } else {
        ULL a = i - p - 1 >= 0 ? buckets[i - p - 1] >> (64 - w) : 0;
        ULL b = i - p >= 0 ? buckets[i - p] << w : 0;
        buckets[i] = a | b;
      }
    }
    align_last_bucket();
    return *this;
  }
  Bitset operator<<(int m) const { Bitset ret = *this; return ret <<= m; }

  int touch(int l, int r) const {  // return lowbit in [l, r]
    int lat = l >> 6;
    int rat = r >> 6;
    for (int i = 0; i < 64; ++i) if (buckets[lat] >> i & 1) {
      int w = (lat << 6) + i;
      if (l <= w && w <= r) return w;
    }
    for (int i = lat + 1; i < rat; ++i) if (buckets[i]) {
      return (i << 6) + lowbit(buckets[i]);
    }
    for (int i = 0; i < 64; ++i) if (buckets[rat] >> i & 1) {
      int w = (rat << 6) + i;
      if (l <= w && w <= r) return w;
    }
    return -1;
  }

  std::string to_string() const {
    std::stringstream ss;
    for (int i = (int)buckets.size() - 1; i >= 0; --i) {
      ss << std::hex << buckets[i];
      if (i) ss << "-";
    }
    return ss.str();
  }

 private:
  using ULL = unsigned long long;

  static int get_bucket_size(int n) { return ((n - 1) >> 6) + 1; }
  static int lowbit(ULL val) { return __builtin_ffsll(val) - 1; }

  // [0, n)
  bool in_range(int p) const { return 0 <= p && p < n; }

  void align_last_bucket_of(int m) {
    if (!(m & 63)) return;
    buckets[get_bucket_size(m) - 1] &= ((1ULL << (m & 63)) - 1);
  }
  void align_last_bucket() { align_last_bucket_of(n); }

  int n = 0;
  std::vector<ULL> buckets;
};

std::string to_string(const Bitset& bitset) {
  return bitset.to_string();
}

