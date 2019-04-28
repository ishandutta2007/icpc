struct SuffixArray {
  int n;
  std::string str;
  std::vector<int> sa, rank;

  template <typename Compare>
    int binarySearch(const std::string &t) {
      int m = t.size();
      int lb = -1, ub = n + 1;
      while (ub - lb > 1) {
        int mid = (ub + lb) / 2;
        if (Compare()(strncmp(str.c_str() + sa[mid], t.c_str(), m), 0)) {
          lb = mid;
        } else {
          ub = mid;
        }
      }
      return ub;
    }

  // O(n(logn)^2) construction.
  SuffixArray(const std::string& _s) : n(_s.size()), str(_s), sa(n + 1), rank(n + 1) {
    for (int i = 0; i <= n; i++) {
      sa[i] = i;
      rank[i] = i < n ? str[i] : -1;
    }
    std::vector<int> tmp(n + 1);
    for (int k = 1; k <= n; k *= 2) {
      // (rank[i], rank[i+k]), (rank[j], rank[j+k]) ¤ò±ÈÝ^
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
      for (int i = 0; i <= n; i++) {
        rank[i] = tmp[i];
      }
    }
  }

  // O(|t|logn).
  bool contain(const std::string &t) {
    int lb = 0, ub = n;
    while (ub - lb > 1) {
      int mid = (lb + ub) / 2;
      if (str.compare(sa[mid], t.size(), t) < 0)
        lb = mid;
      else
        ub = mid;
    }
    return str.compare(sa[ub], t.size(), t) == 0;
  }

  // O(n).
  // lcp[i] means lcp(str[sa[i]..], str[sa[i + 1]..]).
  std::vector<int> get_lcp() {
    for (int i = 0; i <= n; i++)
      rank[sa[i]] = i;
    int h = 0;
    std::vector<int> lcp(n + 1);
    for (int i = 0; i < n; i++) {
      int j = sa[rank[i] - 1];
      if (h > 0)
        h--;
      for (; j + h < n && i + h < n; h++) {
        if (str[j + h] != str[i + h])
          break;
      }
      lcp[rank[i] - 1] = h;
    }
    return lcp;
  }
  std::vector<int> get_sa() {
    return sa;
  }
  int lower_bound(const std::string &t) {
    return binarySearch<std::less<int>>(t);
  }
  int upper_bound(const std::string &t) {
    return binarySearch<std::less_equal<int>>(t);
  }
};

// https://atcoder.jp/contests/kupc2016/tasks/kupc2016_g
int example(const std::string& s) {
  SuffixArray sa(s);
  auto lcp = sa.get_lcp();
  return s.length() - *std::max_element(lcp.begin(), lcp.end());
}
