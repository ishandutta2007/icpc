template<typename String>
struct KnuthMorrisPratt {
  const String& str;
  std::vector<int> next;

  explicit KnuthMorrisPratt(const String& str) : str(str), next(str.size()) {
    if (str.size() == 0) return;
    next[0] = -1;
    for (int i = 1, j = -1; i < str.size(); ++i) {
      while (j >= 0 && str[i] != str[j + 1]) j = next[j];
      next[i] = str[i] == str[j + 1] ? ++j : -1;
    }
  }

  int count_occurrence(const String& s) const {
    int ret = 0;
    for (int i = 0, j = -1; i < s.length(); ++i) {
      while (j >= 0 && s[i] != str[j + 1]) j = next[j];
      if (s[i] == str[j + 1]) {
        ++j;
        if (j + 1 == str.length()) {
          j = next[j];
          ++ret;
        }
      }
    }
    return ret;
  }
};

