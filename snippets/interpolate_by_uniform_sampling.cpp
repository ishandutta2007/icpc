template<typename T>
T interpolate_by_uniform_sampling(T x0, T strip, const std::vector<T>& ys, T x) {
  int k = (int)ys.size() - 1;
  assert(k >= 0);
  if (auto t = (long long)((x - x0) / strip); t <= k && strip * t == x - x0) return ys[t];
  // x_i = x_0 + i * strip.
  // By Lagrange interpolation we have:
  // L(x) = \sum_{i=0}^{k} y_i * l_i(x),
  // where l_i(x) = \Pi_{j=0, j!=i}^{k} (x-x_j)/(x_i-x_j).
  //
  // Since it's from unifrom sampling, x_{i+1}-x_{i}=x_{i}-x_{i-1}=strip, we have:
  // l_{i+1}(x) = l_i(x)*(x-x_i)/(x-x_{i+1})/(i+1)*(i-k).
  //
  // O(klog(A)).
  T l = 1;
  for (int j = 1; j <= k; ++j) l = l * (x - (x0 + strip * j)) / (-strip * j);
  T ret = 0;
  for (int i = 0; i <= k; ++i) {
    ret += ys[i] * l;
    if (i != k) l = l * (x - (x0 + strip * i)) / (x - (x0 + strip * (i + 1))) / (i + 1) * (i - k);
  }
  return ret;
}

