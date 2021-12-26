template<typename T, typename Func, typename R = typename std::result_of<Func&(T)>::type>
R ternary_search(const std::vector<T>& candidate_points, Func&& func) {
  int l = 0, r = (int)candidate_points.size() - 1;
  if (r - l > 6) {
    while (r - l > 2) {
      int lmid = (l * 2 + r) / 3;
      int rmid = (l + r * 2) / 3;
      if (func(candidate_points[lmid]) > func(candidate_points[rmid])) l = lmid;
      else r = rmid;
    }
  }
  R result = std::numeric_limits<R>::max();
  for (int i = std::max(0, l - 2); i <= r + 2 && i < candidate_points.size(); ++i) {
    result = std::min(result, func(candidate_points[i]));
  }
  return result;
}

