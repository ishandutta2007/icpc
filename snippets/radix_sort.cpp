template<typename RandomAccessIterator, typename GetKey>  // GetKey :: Element -> int
void radix_sort(RandomAccessIterator begin, RandomAccessIterator end, GetKey&& get_key) {
  const int n = std::distance(begin, end);
  if (n == 0) return;
  int L = 1;
  while (1 << (L + 1) <= n) ++L;
  const int m = 1 << L;
  const int mask = m - 1;
  int mx = 0;
  for (auto iter = begin; iter != end; ++iter) mx = std::max(mx, get_key(*iter));
  using ElemType = std::remove_reference_t<decltype(*begin)>;
  std::vector<ElemType> b(n);
  std::vector<int> bucket_size(m);
  for (int step = 0; mx >> (L * step); ++step) {
    std::fill(bucket_size.begin(), bucket_size.end(), 0);
    for (auto iter = begin; iter != end; ++iter) {
      ++bucket_size[get_key(*iter) >> (L * step) & mask];
    }
    for (int i = 1; i < m; ++i) bucket_size[i] += bucket_size[i - 1];
    for (int i = n - 1; i >= 0; --i) {
      b[--bucket_size[get_key(*(begin + i)) >> (L * step) & mask]] = *(begin + i);
    }
    std::copy(b.begin(), b.end(), begin);
  }
}

