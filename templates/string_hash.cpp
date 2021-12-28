struct StringHash {
  using ULL = unsigned long long;
  static const ULL seed = 214142131331;
  static std::vector<ULL> pw;

  int n;
  std::vector<ULL> table;

  explicit StringHash(const std::string& str) : n(str.length()), table(str.length() + 1, 0) {
    for (int i = n - 1; i >= 0; --i) {
      table[i] = str[i] + table[i + 1] * seed;
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

  ULL hash(int l, int r) const {
    CHECK(l <= r);
    CHECK(r < n);
    return table[l] - table[r + 1] * pw[r - l + 1];
  }

  int get_lcp(int x, int y) const {
    int L = 1, R = std::min(n - x, n - y);
    while (L <= R) {
      int mid = (L + R) >> 1;
      if (hash(x, x + mid - 1) == hash(y, y + mid - 1)) {
        L = mid + 1;
      } else {
        R = mid - 1;
      }
    }
    return L - 1;
  }
};

std::vector<ULL> StringHash::pw;

