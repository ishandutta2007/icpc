#pragma GCC target ("avx")

#include <bits/stdc++.h>
#ifdef ALGO
#include "el_psy_congroo.hpp"
#else
#define DUMP(...) 1145141919810
#define CHECK(...) (__VA_ARGS__)
#endif

namespace {

using LL = long long;
const int kN = 500000 + 5;
const int MAGIC = 1000;
const int NUMERIC_MAGIC = 70;
int n, m;
int a[kN];
LL result[kN];
int mx;

std::vector<int> divisors[kN];

LL order_change[kN];

struct Query {
  int l, r, id;
};

Query queries[kN];

struct Event {
  int anchor, l, r, order;
  LL val;

  Event(int anchor, int l, int r, int order) : anchor(anchor), l(l), r(r), order(order), val(0) {}
};

std::vector<Event> prefixes, suffixes;

LL tmp[kN];

void prepare() {
  std::sort(queries, queries + m, [](const Query& lhs, const Query& rhs) {
    if (lhs.l / MAGIC != rhs.l / MAGIC) return lhs.l < rhs.l;
    return (lhs.l / MAGIC & 1) ? lhs.r < rhs.r : lhs.r > rhs.r;
  });
  prefixes.reserve(m * 2);
  suffixes.reserve(m * 2);
  // NOTE: We can unify 'suffixes' into 'prefixes',
  // but you will need to handle some single-point values manually.
  for (int i = 0, ll = n, rr = n - 1; i < m; ++i) {
    int L = queries[i].l;
    int R = queries[i].r;
    if (L < ll) {
      suffixes.emplace_back(rr + 1, L, ll - 1, i << 1);
      // prefixes.emplace_back(rr, L, ll - 1, i << 1 | 1);
      // prefixes.back().val += (ll - L) * 2;
      ll = L;
    }
    if (rr < R) {
      prefixes.emplace_back(ll - 1, rr + 1, R, i << 1);
      rr = R;
    }
    if (ll < L) {
      suffixes.emplace_back(rr + 1, ll, L - 1, i << 1 | 1);
      // prefixes.emplace_back(rr, ll, L - 1, i << 1);
      // prefixes.back().val += (L - ll) * 2;
      ll = L;
    }
    if (R < rr) {
      prefixes.emplace_back(ll - 1, R + 1, rr, i << 1 | 1);
      rr = R;
    }
  }
  std::sort(prefixes.begin(), prefixes.end(), [](const Event& lhs, const Event& rhs) {
    return lhs.anchor < rhs.anchor;
  });
  std::sort(suffixes.begin(), suffixes.end(), [](const Event& lhs, const Event& rhs) {
    return lhs.anchor < rhs.anchor;
  });
}

struct LargeSolver {
  int cnt[kN];

  void init() {
    memset(cnt, 0, sizeof(int) * (mx + 1));
  }

  void put(int x) {
    if (x < NUMERIC_MAGIC) return;
    for (int y : divisors[x]) ++cnt[y];
    for (int y = x; y <= mx; y += x) ++cnt[y];
  }

  // Query should have an O(1) complexicity.
  int query(int x) const {
    return cnt[x];
  }

  void solve() {
    this->init();
    LL val1, val2, val3, val4, val5, val6, val7;
    for (int i = 0, j = 0; i < n; ++i) {
      while (j < prefixes.size() && prefixes[j].anchor < i) {
        Event& event = prefixes[j++];
        LL val = 0;
        int k = event.l;
        int r = event.r;
        if (k + 7 <= r) {
          val1 = 0;
          val2 = 0;
          val3 = 0;
          val4 = 0;
          val5 = 0;
          val6 = 0;
          val7 = 0;
          for (; k + 7 <= r; k += 8) {
            val -= this->query(a[k]);
            val1 -= this->query(a[k + 1]);
            val2 -= this->query(a[k + 2]);
            val3 -= this->query(a[k + 3]);
            val4 -= this->query(a[k + 4]);
            val5 -= this->query(a[k + 5]);
            val6 -= this->query(a[k + 6]);
            val7 -= this->query(a[k + 7]);
          }
          val += val1 + val2 + val3 + val4 + val5 + val6 + val7;
        }
        for (; k <= r; ++k) {
          val -= this->query(a[k]);
        }
        event.val += val;
      }
      tmp[i] = this->query(a[i]);
      this->put(a[i]);
    }
    tmp[n] = 0;
    for (int i = n - 1; i >= 0; --i) tmp[i] += tmp[i + 1];
    for (Event& event : prefixes) {
      event.val += tmp[event.l] - tmp[event.r + 1];
    }

    this->init();
    for (int i = n - 1, j = (int)suffixes.size() - 1; i >= 0; --i) {
      while (j >= 0 && suffixes[j].anchor > i) {
        Event& event = suffixes[j--];
        LL val = 0;
        int k = event.l;
        int r = event.r;
        if (k + 7 <= r) {
          val1 = 0;
          val2 = 0;
          val3 = 0;
          val4 = 0;
          val5 = 0;
          val6 = 0;
          val7 = 0;
          for (; k + 7 <= r; k += 8) {
            val -= this->query(a[k]);
            val1 -= this->query(a[k + 1]);
            val2 -= this->query(a[k + 2]);
            val3 -= this->query(a[k + 3]);
            val4 -= this->query(a[k + 4]);
            val5 -= this->query(a[k + 5]);
            val6 -= this->query(a[k + 6]);
            val7 -= this->query(a[k + 7]);
          }
          val += val1 + val2 + val3 + val4 + val5 + val6 + val7;
        }
        for (; k <= r; ++k) {
          val -= this->query(a[k]);
        }
        event.val += val;
      }
      tmp[i] = this->query(a[i]);
      this->put(a[i]);
    }
    tmp[n] = 0;
    for (int i = n - 1; i >= 0; --i) tmp[i] += tmp[i + 1];
    for (Event& event : suffixes) {
      event.val += tmp[event.l] - tmp[event.r + 1];
    }
  }
} large_solver;

struct SmallSolver {
  int cnt;

  void init() {
    this->cnt = 0;
  }

  void put(int type) {
    if (type == 2) ++cnt;
  }

  // Query should have an O(1) complexicity.
  int query(int type) const {
    return type == 0 ? 0 : (cnt << type >> 1);
  }

  void solve(int key) {
    static int8_t types[kN];
    static int relative[kN];
    relative[n] = 0;
    for (int i = n - 1; i >= 0; --i) {
      types[i] = a[i] == key ? 2 : std::max(a[i], key) % std::min(a[i], key) == 0;
      relative[i] = relative[i + 1] + types[i];
    }

    this->init();
    for (int i = 0, j = 0; i < n; ++i) {
      while (j < prefixes.size() && prefixes[j].anchor < i) {
        Event& event = prefixes[j++];
        event.val -= LL(cnt) * (relative[event.l] - relative[event.r + 1]);
      }
      tmp[i] = this->query(types[i]);
      this->put(types[i]);
    }
    tmp[n] = 0;
    for (int i = n - 1; i >= 0; --i) tmp[i] += tmp[i + 1];
    for (Event& event : prefixes) {
      event.val += tmp[event.l] - tmp[event.r + 1];
    }

    this->init();
    for (int i = n - 1, j = (int)suffixes.size() - 1; i >= 0; --i) {
      while (j >= 0 && suffixes[j].anchor > i) {
        Event& event = suffixes[j--];
        event.val -= LL(cnt) * (relative[event.l] - relative[event.r + 1]);
      }
      tmp[i] = this->query(types[i]);
      this->put(types[i]);
    }
    tmp[n] = 0;
    for (int i = n - 1; i >= 0; --i) tmp[i] += tmp[i + 1];
    for (Event& event : suffixes) {
      event.val += tmp[event.l] - tmp[event.r + 1];
    }
  }
} small_solver;

void solve() {
  for (int i = 1; i <= mx; ++i) divisors[i].reserve(8);
  for (int i = 1; i <= mx; ++i)
    for (int j = i; j <= mx; j += i)
      divisors[j].emplace_back(i);

  prepare();

  large_solver.solve();

  std::vector<bool> exists(NUMERIC_MAGIC);
  for (int i = 0; i < n; ++i) if (a[i] < NUMERIC_MAGIC) exists[a[i]] = true;
  for (int i = 0; i < NUMERIC_MAGIC; ++i) if (exists[i]) small_solver.solve(i);

  for (const Event& event : prefixes)
    order_change[event.order >> 1] += ~event.order & 1 ? event.val : -event.val;
  for (const Event& event : suffixes)
    order_change[event.order >> 1] += ~event.order & 1 ? event.val : -event.val;
  LL val = 0;
  for (int i = 0; i < m; ++i) {
    val += order_change[i];
    result[queries[i].id] += val;
  }
}

struct IO {
  IO(FILE *in = stdin) : in(in) {}

  IO& operator >> (int& x) {
    x = next_int();
    return *this;
  }

  int next_char() {
    if (position == length) {
      position = 0, length = fread(buffer, 1, LENGTH, in);
    }
    if (position == length) {
      eof = true;
      return -1;
    }
    return buffer[position++];
  }

  int next_uint() {
    int c = next_char(), x = 0;
    while (c <= 32) {
      c = next_char();
    }
    for (; '0' <= c && c <= '9'; c = next_char()) {
      x = x * 10 + c - '0';
    }
    return x;
  }

  int next_int() {
    int s = 1, c = next_char(), x = 0;
    while (c <= 32) {
      c = next_char();
    }
    if (c == '-') {
      s = -1, c = next_char();
    }
    for (; '0' <= c && c <= '9'; c = next_char()) {
      x = x * 10 + c - '0';
    }
    return x * s;
  }

  void next_string(char *s) {
    int c = next_char();
    while (c <= 32) {
      c = next_char();
    }
    for (; c > 32; c = next_char()) {
      *s++ = c;
    }
    *s = 0;
  }

private:
  static const int LENGTH = 1 << 16;

  char buffer[LENGTH];
  int position = 0, length = 0;
  bool eof = false;
  FILE *in;
};

}  // namespace

int main() {
  IO reader;
  // std::ios::sync_with_stdio(false);
  // std::cin.tie(nullptr);
  // std::istream& reader = std::cin;

  reader >> n >> m;
  for (int i = 0; i < n; ++i) {
    reader >> a[i];
  }
  mx = *std::max_element(a, a + n);
  for (int i = 0; i < m; ++i) {
    reader >> queries[i].l >> queries[i].r; --queries[i].l; --queries[i].r;
    result[i] += queries[i].r - queries[i].l + 1;
    queries[i].id = i;
  }
  solve();
  for (int i = 0; i < m; ++i) {
    printf("%lld\n", result[i]);
  }
}

