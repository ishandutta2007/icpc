template<typename T, typename Comparator = std::less<T>>
struct SparseTable {
  std::vector<std::vector<T>> u;
  std::vector<int> lg;
  Comparator cmp;

  void build(const std::vector<T>& a) {
    int n = a.size(), L = 1;
    while ((1 << L) <= n) ++L;
    std::vector<std::vector<T>>(n, std::vector<T>(L)).swap(u);
    lg.resize(n + 1);
    lg[0] = -1;
    for (int i = 1; i < lg.size(); ++ i) lg[i] = lg[i >> 1] + 1;
    for (int i = 0; i < n; ++ i) u[i][0] = a[i];
    for (int j = 1; (1 << j) <= n; ++ j) {
      for (int i = 0; i + (1 << j) <= n; ++ i) {
        u[i][j] = select(u[i][j - 1], u[i + (1 << (j - 1))][j - 1]);
      }
    }
  }
  T ask(int a, int b) const {  // [a, b]
    if (a > b || a < 0 || b >= u.size()) throw;
    int k = lg[b - a + 1];
    return select(u[a][k], u[b - (1 << k) + 1][k]);
  }
  T select(const T& lhs, const T& rhs) const { return cmp(lhs, rhs) ? lhs : rhs; }
};

// SparseTable<int> st;
// SparseTable<int, std::greater<int>> st;

template<typename StringType = std::string>
struct SuffixArray {
 public:
  int n;
  StringType str;
  std::vector<int> sa, rank;

  // lcp[i] means lcp(str[sa[i]..], str[sa[i + 1]..]).
  std::vector<int> lcp;

  SparseTable<int, std::less<int>> st;

  // NOTE: Due to implementation issue, you should not use 0 in your charset.
  explicit SuffixArray(const StringType& s) : n(s.size()), str(s), sa(n + 1), rank(n + 1) {
    if (n > 0) {
      this->len = n;
      int m = *std::max_element(str.begin(), str.end()) + 1;
      std::vector<int> buffer((std::max(m, (n + 1) / 2) + 1) * 2);
      this->buffer = &buffer[0];
      using T = typename std::decay_t<decltype(str[0])>;
      sa_is<T>(&str[0], &sa[0], n + 1, m);
    }
    for (int i = 0; i <= n; ++i) rank[sa[i]] = i;

    lcp.resize(n, 0);
    int h = 0;
    for (int i = 0; i < n; ++i) {
      int j = sa[rank[i] - 1];
      if (h > 0) --h;
      for (; j + h < n && i + h < n; ++h) {
        if (str[j + h] != str[i + h]) break;
      }
      lcp[rank[i] - 1] = h;
    }
  }

  // Not verified yet.
  int compare(const StringType& lhs, int pos, int len, const StringType& rhs) const {
    for (int i = pos; i < pos + len; ++i) {
      if (i >= lhs.size()) {
        return i - pos >= rhs.size() ? 0 : -1;
      }
      if (i - pos >= rhs.size()) {
        return 1;
      }
      if (lhs[i] != rhs[i - pos]) {
        return lhs[i] - rhs[i - pos];
      }
    }
    return len < rhs.size() ? -1 : 0;
  }

  template <typename Compare> int binary_search(const StringType& t) const {
    int lb = -1, ub = n + 1;
    while (ub - lb > 1) {
      int mid = (ub + lb) / 2;
      if (Compare()(compare(str, sa[mid], t.size(), t), 0))
        lb = mid;
      else
        ub = mid;
    }
    return ub;
  }

  // O(|t|logn).
  bool contains(const StringType& t) const {
    int lb = 0, ub = n;
    while (ub - lb > 1) {
      int mid = (lb + ub) / 2;
      if (compare(str, sa[mid], t.size(), t) < 0)
        lb = mid;
      else
        ub = mid;
    }
    return compare(str, sa[ub], t.size(), t) == 0;
  }

  void prepare_lcp_rmq() {
    st.build(lcp);
  }

  // lcp(str[x..], str[y..])
  int get_lcp(int x, int y) const {
    if (x == y) return n - x;
    if (rank[x] > rank[y]) std::swap(x, y);
    return st.ask(rank[x], rank[y] - 1);
  }

  int lower_bound(const StringType& t) const { return binary_search<std::less<int>>(t); }
  int upper_bound(const StringType& t) const { return binary_search<std::less_equal<int>>(t); }

 private:
  using SLTypes = std::vector<bool>;
  int* buffer = nullptr;
  int* freq = nullptr;
  int* cur = nullptr;
  int len = 0;

  template<typename T>
  void count_frequency(const T* s, int n, int m) {
    memset(freq, 0, sizeof(int) * m);
    for (int i = 0; i < n; ++i) ++freq[(int)s[i]];
    for (int i = 1; i < m; ++i) freq[i] += freq[i - 1];
    memcpy(cur, freq, sizeof(int) * m);
  }

#define pushS(x) sa[--cur[(int)s[x]]] = x
#define pushL(x) sa[cur[(int)s[x]]++] = x
  template<typename T>
  void induce(const T* s, int* sa, int m, const SLTypes& t) {
    const int n = t.size();
    memcpy(cur + 1, freq, sizeof(int) * (m - 1));
    for (int i = 0; i < n; ++i) {
      int p = sa[i] - 1;
      if (p >= 0 && t[p]) pushL(p);
    }
    memcpy(cur, freq, sizeof(int) * m);
    for (int i = n - 1; i > 0; --i) {
      int p = sa[i] - 1;
      if (p >= 0 && !t[p]) pushS(p);
    }
  }

  template<typename T>
  void sa_is(const T* s, int* sa, int n, int m) {
    SLTypes t(n); memset(sa, 0, sizeof(int) * n);
    for (int i = n - 2; ~i; --i) {
      t[i] = (s[i] == s[i + 1]) ? t[i + 1] : s[i] > s[i + 1];
    }
    freq = buffer, cur = buffer + m;
    count_frequency(s, n, m);
    for (int i = 1; i < n; ++i) if (t[i - 1] > t[i]) pushS(i);
    induce(s, sa, m, t);
    int n1 = 0, order = 0;
    for (int i = 0, p; i < n; ++i) {
      if ((p = sa[i]) && t[p - 1] > t[p]) sa[n1++] = p;
    }
    int* s1 = sa + n1;
    memset(s1, -1, sizeof(int) * (n - n1));
    s1[(sa[0] - 1) / 2] = order++;
    for (int i = 1; i < n1; ++i) {
      bool diff = true;
      for (int x = sa[i - 1], y = sa[i]; ; ++x, ++y) {
        if (s[x] != s[y] || t[x] != t[y]) break;
        else if (t[x] > t[x + 1] && t[y] > t[y + 1]) {
          diff = (s[x + 1] != s[y + 1]); break;
        }
      }
      s1[(sa[i] - 1) / 2] = (order += diff) - 1;
    }
    for (int i = 0, x = 0; i < n - n1; ++i) {
      if (~s1[i]) s1[x++] = s1[i];
    }
    if (order != n1) {
      sa_is<int>(s1, sa, n1, order);
      for (int i = 0; i < n1; ++i) s1[sa[i]] = i;
    }
    for (int i = 1, j = 0; i < n; ++i) {
      if (t[i - 1] > t[i]) sa[s1[j++]] = -i;
    }
    memset(s1, 0, sizeof(int) * (n - n1));
    freq = buffer, cur = buffer + m;
    count_frequency(s, n, m);
    for (int i = n1 - 1; ~i; --i) pushS(-sa[i]);
    induce(s, sa, m, t);
  }
#undef pushS
#undef pushL
};

