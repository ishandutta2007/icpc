template<typename T>
struct SparseTable {
  std::vector<std::vector<T>> u;
  std::vector<int> lg;
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
        u[i][j] = std::min(u[i][j - 1], u[i + (1 << (j - 1))][j - 1]);
      }
    }
  }
  T ask(int a, int b) const {  // [a, b]
    if (a > b || a < 0 || b >= u.size()) throw;
    int k = lg[b - a + 1];
    return std::min(u[a][k], u[b - (1 << k) + 1][k]);
  }
};

template<typename StringType = std::string>
struct SuffixArray {
  int n;
  StringType str;
  std::vector<int> sa, rank;

  // lcp[i] means lcp(str[sa[i]..], str[sa[i + 1]..]).
  std::vector<int> lcp;

  SparseTable<int> st;

  // O(n(logn)^2) construction.
  SuffixArray(const StringType& _s) : n(_s.size()), str(_s), sa(n + 1), rank(n + 1) {
    for (int i = 0; i <= n; ++i) {
      sa[i] = i;
      rank[i] = i < n ? str[i] : -1;
    }
    std::vector<int> tmp(n + 1);
    for (int k = 1; k <= n; k <<= 1) {
      // (rank[i], rank[i+k]), (rank[j], rank[j+k]) comparasion.
      auto compare_sa = [=](int i, int j) {
        if (rank[i] != rank[j])
          return rank[i] < rank[j];
        else {
          int ri = i + k <= n ? rank[i + k] : -1;
          int rj = j + k <= n ? rank[j + k] : -1;
          return ri < rj;
        }
      };
      std::sort(sa.begin(), sa.end(), compare_sa);
      tmp[sa[0]] = 0;
      for (int i = 1; i <= n; i++) {
        tmp[sa[i]] = tmp[sa[i - 1]] + (compare_sa(sa[i - 1], sa[i]) ? 1 : 0);
      }
      rank.swap(tmp);
    }
    for (int i = 0; i <= n; ++i) rank[sa[i]] = i;

    lcp.resize(n + 1, 0);
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
};

// https://atcoder.jp/contests/kupc2016/tasks/kupc2016_g
int example(const std::string& s) {
  SuffixArray<std::string> sa(s);
  return s.size() - *std::max_element(sa.lcp.begin(), sa.lcp.end());
}

void test() {
  printf("%d\n", 3 == example("abcabc"));
  printf("%d\n", 7 == example("abracadabra"));
  printf("%d\n", 8 == example("abcbabbcabbc"));
  printf("%d\n", 44 == example("bbcacbcbcabbabacccbbcacbaaababbacabaaccbccabcaabba"));
}

