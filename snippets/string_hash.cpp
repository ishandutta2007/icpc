// template<int MOD>
// bool operator<(const Integral<MOD>& lhs, const Integral<MOD>& rhs) {
//   return lhs.val() < rhs.val();
// }

template<typename HashType = unsigned long long>
struct StringHash {
  static HashType seed;
  static std::vector<HashType> pw;

  int n;
  std::vector<HashType> table;

  explicit StringHash(const std::string& str) : n(str.length()), table(str.length() + 1, 0) {
    for (int i = n - 1; i >= 0; --i) {
      table[i] = table[i + 1] * seed + str[i];
    }
    if (pw.size() <= str.length()) {
      int last = pw.size();
      pw.resize(str.length() + 1);
      for (int i = last; i < pw.size(); ++i) {
        pw[i] = i == 0 ? 1 : pw[i - 1] * seed;
      }
    }
  }

  int size() const { return n; }
  int length() const { return size(); }

  HashType get(int l, int r) const {  // [l, r]
    CHECK(l <= r);
    CHECK(r < n);
    return table[l] - table[r + 1] * pw[r - l + 1];
  }

  // lcp of str[x..] and str[y..].
  int get_lcp(int x, int y) const {
    int L = 1, R = std::min(n - x, n - y);
    while (L <= R) {
      int mid = (L + R) >> 1;
      if (get(x, x + mid - 1) == get(y, y + mid - 1)) {
        L = mid + 1;
      } else {
        R = mid - 1;
      }
    }
    return L - 1;
  }

  static bool lt(const StringHash& x, int xl, int xr, const StringHash& y, int yl, int yr) {  // x[xl, xr] < y[yl, yr]
    int len = std::min(xr - xl + 1, yr - yl + 1);
    assert(len > 0);
    int l = 1, r = len;
    while (l <= r) {
      int mid = (l + r) >> 1;
      if (x.get(xl, xl + mid - 1) == y.get(yl, yl + mid - 1)) l = mid + 1;
      else r = mid - 1;
    }
    int lcp = l - 1;
    if (xr - xl + 1 == lcp && yr - yl + 1 == lcp) return false;  // eq
    if (xr - xl + 1 == lcp) return true;
    if (yr - yl + 1 == lcp) return false;

    // Assume the HashType is comparable and it preserves lexicographical order.
    return x.get(xl + lcp, xl + lcp) < y.get(yl + lcp, yl + lcp);
  }
  static bool gt(const StringHash& x, int xl, int xr, const StringHash& y, int yl, int yr) {  // x[xl, xr] > y[yl, yr]
    return lt(y, yl, yr, x, xl, xr);
  }
  static bool le(const StringHash& x, int xl, int xr, const StringHash& y, int yl, int yr) {  // x[xl, xr] <= y[yl, yr]
    return !gt(x, xl, xr, y, yl, yr);
  }
  static bool ge(const StringHash& x, int xl, int xr, const StringHash& y, int yl, int yr) {  // x[xl, xr] >= y[yl, yr]
    return !lt(x, xl, xr, y, yl, yr);
  }
};

template<typename HashType>
HashType StringHash<HashType>::seed = 214131331;

template<typename HashType>
std::vector<HashType> StringHash<HashType>::pw;

using Hash = StringHash<>;

