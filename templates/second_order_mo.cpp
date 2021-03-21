#include <bits/stdc++.h>
#ifdef ALGO
#include "el_psy_congroo.hpp"
#else
#define DUMP(...) 1145141919810
#define CHECK(...) (__VA_ARGS__)
#endif

namespace {

using LL = long long;
const int kN = 100000 + 5;
const int BIT = 14;
const int MAGIC = 350;
int n, m, k;
int a[kN];
int l[kN], r[kN];
LL result[kN];

int order[kN];
LL order_change[kN];

std::vector<int> target_sets;

struct Container {
  int cnt[1 << BIT];

  void init() {
    memset(cnt, 0, sizeof(cnt));
  }

  void put(int x) {
    for (int mask : target_sets) cnt[mask ^ x]++;
  }

  // Query should have an O(1) complexicity.
  int query(int x) const {
    return cnt[x];
  }
} container;

struct Event {
  int anchor, l, r, order, sign;
};

void solve() {
  for (int mask = 0; mask < 1 << BIT; ++mask) {
    if (__builtin_popcount(mask) == k) target_sets.emplace_back(mask);
  }
  std::iota(order, order + m, 0);
  std::sort(order, order + m, [&](int x, int y) {
    if (l[x] / MAGIC != l[y] / MAGIC) return l[x] < l[y];
    return (l[x] / MAGIC) & 1 ? r[x] < r[y] : r[x] > r[y];
  });
  std::vector<Event> prefixes, suffixes;
  for (int i = 0, ll = n, rr = n - 1; i < m; ++i) {
    int L = l[order[i]];
    int R = r[order[i]];
    if (L < ll) {
      suffixes.emplace_back(Event{.anchor = rr + 1, .l = L, .r = ll - 1, .order = i, .sign = 1});
      ll = L;
    }
    if (rr < R) {
      prefixes.emplace_back(Event{.anchor = ll - 1, .l = rr + 1, .r = R, .order = i, .sign = 1});
      rr = R;
    }
    if (ll < L) {
      suffixes.emplace_back(Event{.anchor = rr + 1, .l = ll, .r = L - 1, .order = i, .sign = -1});
      ll = L;
    }
    if (R < rr) {
      prefixes.emplace_back(Event{.anchor = ll - 1, .l = R + 1, .r = rr, .order = i, .sign = -1});
      rr = R;
    }
  }
  static LL tmp[kN];
  std::sort(prefixes.begin(), prefixes.end(), [](const Event& lhs, const Event& rhs) {
    return lhs.anchor < rhs.anchor;
  });
  container.init();
  for (int i = 0, j = 0; i < n; ++i) {
    while (j < prefixes.size() && prefixes[j].anchor < i) {
      CHECK(prefixes[j].anchor == i - 1);
      const Event& event = prefixes[j++];
      LL val = 0;
      for (int k = event.l; k <= event.r; ++k) {
        val -= container.query(a[k]);
      }
      order_change[event.order] += event.sign == 1 ? val : -val;
    }
    tmp[i] = container.query(a[i]);
    container.put(a[i]);
  }
  tmp[n] = 0;
  for (int i = n - 1; i >= 0; --i) tmp[i] += tmp[i + 1];
  for (const Event& event : prefixes) {
    LL val = tmp[event.l] - tmp[event.r + 1];
    order_change[event.order] += event.sign == 1 ? val : -val;
  }

  std::sort(suffixes.begin(), suffixes.end(), [](const Event& lhs, const Event& rhs) {
    return lhs.anchor < rhs.anchor;
  });
  container.init();
  for (int i = n - 1, j = (int)suffixes.size() - 1; i >= 0; --i) {
    while (j >= 0 && suffixes[j].anchor > i) {
      CHECK(suffixes[j].anchor == i + 1);
      const Event& event = suffixes[j--];
      LL val = 0;
      for (int k = event.l; k <= event.r; ++k) {
        val -= container.query(a[k]);
      }
      order_change[event.order] += event.sign == 1 ? val : -val;
    }
    tmp[i] = container.query(a[i]);
    container.put(a[i]);
  }
  tmp[n] = 0;
  for (int i = n - 1; i >= 0; --i) tmp[i] += tmp[i + 1];
  for (const Event& event : suffixes) {
    LL val = tmp[event.l] - tmp[event.r + 1];
    order_change[event.order] += event.sign == 1 ? val : -val;
  }

  for (int i = 0; i < m; ++i) {
    if (i) order_change[i] += order_change[i - 1];
    result[order[i]] = order_change[i];
  }
}

}  // namespace

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::istream& reader = std::cin;

  reader >> n >> m >> k;
  for (int i = 0; i < n; ++i) {
    reader >> a[i];
  }
  for (int i = 0; i < m; ++i) {
    reader >> l[i] >> r[i]; --l[i]; --r[i];
  }
  solve();
  for (int i = 0; i < m; ++i) {
    printf("%lld\n", result[i]);
  }
}

