std::vector<int> prepare(const std::string& w) {
  std::vector<int> next(w.size());
  next[0] = -1;
  for (int i = 1, j = -1; i < w.size(); ++i) {
    while (j >= 0 && w[i] != w[j + 1]) j = next[j];
    next[i] = w[i] == w[j + 1] ? ++j : -1;
  }
  return next;
}

int count_occurrence(const std::string& s, const std::string& w, const std::vector<int>& next) {
  int ret = 0;
  for (int i = 0, j = -1; i < s.length(); ++i) {
    while (j >= 0 && s[i] != w[j + 1]) j = next[j];
    if (s[i] == w[j + 1]) {
      ++j;
      if (j + 1 == w.length()) {
        j = next[j];
        ++ret;
      }
    }
  }
  return ret;
}
