struct BabyStepGiantStep {
 public:
  // Given a cyclic group G of order n, a generator a of the group,
  // and a group element b, the problem is to find an integer x such that a^x=b.
  // Rewrite x: x=im+j, where m=ceil(sqrt(n)), 0<=i<m, 0<=j<m.
  // Then we have:
  // a^x=b, a^{im+j}=b, a^j=b(a^{-m})^i.
  // The algorithm precomputes a^j for some j. Then it fixes an m and tries values of i
  // in the right-hand side.
  //
  // In short, find x s.t. a^x = b mod n.
  // Returns -1 if not found.
  static LL log(LL a, LL b, LL n) {
    assert(n >= 2);
    LL m = std::ceil(std::sqrt(n));
    a %= n;
    b %= n;
    std::unordered_map<LL, LL> map;
    for (LL j = 0, w = 1; j < m; w = w * a % n, ++j) {
      if (w == b) return j;
      map[w] = j;
    }
    LL t = power(power(a, n - 2, n), m, n);
    for (LL i = 0, w = b; i * m < n; w = w * t % n, ++i) {
      auto iter = map.find(w);
      if (iter != map.end()) return i * m + iter->second;
    }
    return -1;
  }

 private:
  using LL = long long;

  static LL power(LL a, LL b, LL mod) {
    LL ret = 1 % mod;
    for ( ; b; b >>= 1, a = a * a % mod) if (b & 1) ret = ret * a % mod;
    return ret;
  }
};

