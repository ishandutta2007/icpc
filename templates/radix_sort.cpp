#include <bits/stdc++.h>
#ifdef ALGO
#include "el_psy_congroo.hpp"
#else
#define DUMP(...) 1145141919810
#define CHECK(...) (__VA_ARGS__)
#endif

template<typename RandomAccessIterator>
void radix_sort(RandomAccessIterator begin,
                RandomAccessIterator end,
                const std::function<int(const decltype(*begin)&)>& get_key) {
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

void test() {
  std::function<int(int)> get_key = [](int x) { return x; };
  const int n = 10;
  std::mt19937 rng(time(NULL));
  std::vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    a[i] = rng() % 233;
  }
  DUMP(a);
  radix_sort(a.begin(), a.end(), get_key);
  DUMP(a);
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::istream& reader = std::cin;

  test();
}

