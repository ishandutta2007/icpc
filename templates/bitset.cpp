#include <bits/stdc++.h>
#ifdef ALGO
#include "el_psy_congroo.hpp"
#else
#define DUMP(...) 1145141919810
#define CHECK(...) (__VA_ARGS__)
#endif

// NOTE: Not been tested yet. Be careful when using it.
struct BitSet {
  using ULL = unsigned long long;
  int n;
  std::vector<ULL> buckets;

  static int get_bucket_size(int n) { return ((n - 1) >> 6) + 1; }

  explicit BitSet(int n) : n(n), buckets(get_bucket_size(n)) {}

  // [0, n)
  bool in_range(int p) const { return 0 <= p && p < n; }

  ULL aligned_last_bucket_of(int m) const {
    const int bucket_id = get_bucket_size(m) - 1;
    const int rest_bits = m - (bucket_id << 6);
    return buckets[bucket_id] & ((1ULL << rest_bits) - 1);
  }
  void align_last_bucket_of(int m) {
    const int last_bucket_id = get_bucket_size(m) - 1;
    buckets[last_bucket_id] = aligned_last_bucket_of(m);
  }

  void flip(int p) { CHECK(in_range(p)); buckets[p >> 6] ^= 1ULL << (p & 63); }
  void flip_all() {
    for (int i = 0; i < buckets.size(); ++i) buckets[i] ^= -1ULL;
    align_last_bucket_of(n);
  }

  bool test(int p) const { CHECK(in_range(p)); return buckets[p >> 6] >> (p & 63) & 1; }
  bool operator [] (int p) const { return test(p); }
  bool all() const {
    for (int i = 0; i + 1 < buckets.size(); ++i) {
      if (~(buckets[i] + 1)) return false;
    }
    const ULL last = (1ULL << (n - ((n - 1) >> 6 << 6))) - 1;
    return buckets.back() == last;
  }
  bool any() const { for (ULL mask : buckets) if (mask) return true; return false; }
  bool none() const { return !any(); }
  int count() const { int ret = 0; for (ULL mask : buckets) ret += __builtin_popcountll(mask); return ret; }
  int size() const { return n; }
  void resize(int m) {
    buckets.resize(get_bucket_size(m));
    if (m < n) align_last_bucket_of(m);
    n = m;
  }

  BitSet& operator &= (const BitSet& other) {
    resize(std::max(size(), other.size()));
    int m = other.size();
    for (int i = ((m - 1) >> 6) + 1; i < (int)buckets.size(); ++i) buckets[i] = 0;
    for (int i = (m - 1) >> 6; i >= 0; --i) buckets[i] &= other.buckets[i];
    align_last_bucket_of(m);
    return *this;
  }
  BitSet operator & (const BitSet& other) const { BitSet ret = *this; return ret &= other; }

  BitSet& operator |= (const BitSet& other) {
    resize(std::max(size(), other.size()));
    for (int i = 0; i < other.buckets.size(); ++i) buckets[i] |= other.buckets[i];
    return *this;
  }
  BitSet operator | (const BitSet& other) const { BitSet ret = *this; return ret |= other; }

  BitSet operator ^= (const BitSet& other) {
    resize(std::max(size(), other.size()));
    for (int i = 0; i < other.buckets.size(); ++i) buckets[i] ^= other.buckets[i];
    return *this;
  }
  BitSet operator ^ (const BitSet& other) const { BitSet ret = *this; return ret ^= other; }

  BitSet operator ~ () const { BitSet ret = *this; ret.flip_all(); return ret; }

  // TODO: Support shift.
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::istream& reader = std::cin;
}

