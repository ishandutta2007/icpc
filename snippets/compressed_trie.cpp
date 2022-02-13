#include <bits/stdc++.h>
#ifdef ALGO
#include "el_psy_congroo.hpp"
#else
#define DUMP(...) 1145141919810
#define CHECK(...) (__VA_ARGS__)
#endif

namespace compressed_trie {

inline bool testbit(unsigned mask, int at) {
  return mask >> at & 1;
}

struct CompressedTrie {
  CompressedTrie* ch[2] = {};
  unsigned val : 27, lowest_eq_bit : 5;  // tag: [0, lowest_eq_bit), bits: [lowest_eq_bit, 27), lowest_eq_bit: [27, 32)

  int cnt = 0;
  unsigned s = 0;

  CompressedTrie() = default;
  CompressedTrie(unsigned w) : val(w), lowest_eq_bit(0), cnt(1), s(w) {}

  unsigned tag() const { return val ^ bits(); }
  unsigned bits() const { return val >> lowest_eq_bit << lowest_eq_bit; }

  void reset_tag() { val = bits(); }

  bool is_compressed() const {
    return (ch[0] == nullptr) ^ (ch[1] == nullptr) ^ 1;
  }

  void up() {
    if (ch[0] == nullptr && ch[1] == nullptr) {
      CHECK(tag() == 0);
      CHECK(lowest_eq_bit == 0);
      s = cnt & 1 ? bits() : 0;
      return;
    }
    CHECK(tag() == 0);
    cnt = 0;
    s = 0;
    if (ch[0]) {
      cnt += ch[0]->cnt;
      s ^= ch[0]->s;
    }
    if (ch[1]) {
      cnt += ch[1]->cnt;
      s ^= ch[1]->s;
    }
    if (cnt & 1) {
      s ^= bits();
    }
  }

  void recieve_bits(unsigned gift) {
    val ^= gift;
    if (cnt & 1) s ^= gift;
  }

  unsigned pop_bits(int at) {
    CHECK(at >= lowest_eq_bit);
    unsigned gift = bits() >> at << at;
    val ^= gift;
    if (cnt & 1) s ^= gift;
    return gift;
  }

  void update(unsigned extra) {
    if (extra == 0) return;
    val ^= extra;
    if (cnt & 1) s ^= extra;
    if (lowest_eq_bit > 0 && testbit(extra, lowest_eq_bit - 1)) {
      std::swap(ch[0], ch[1]);
    }
  }

  void down() {
    if (lowest_eq_bit == 0 || tag() == 0) return;
    if (ch[0]) ch[0]->update(tag());
    if (ch[1]) ch[1]->update(tag());
    reset_tag();
  }
};

// u -> (v -> (left | right) | nullptr) => (u+v) -> (left | right)
// u -> (nullptr | v -> (left | right)) => (u+v) -> (left | right)
CompressedTrie* shrink(CompressedTrie* trie) {
  if (trie == nullptr) return trie;
  if (trie->is_compressed()) return trie;
  CompressedTrie* v = trie->ch[trie->ch[1] != nullptr];
  v->down();
  CHECK(trie->tag() == 0);
  v->recieve_bits(trie->bits());
  v->up();
  delete trie;
  return v;
}

CompressedTrie* merge(CompressedTrie* lhs, CompressedTrie* rhs) {
  if (lhs == nullptr) return rhs;
  if (rhs == nullptr) return lhs;
  if (lhs->lowest_eq_bit == rhs->lowest_eq_bit) {
    if (lhs->bits() == rhs->bits()) {
      if (lhs->lowest_eq_bit == 0) {
        lhs->cnt += rhs->cnt;
        lhs->s ^= rhs->s;
        delete rhs;
        return lhs;
      } else {
        lhs->down();
        rhs->down();
        lhs->ch[0] = merge(lhs->ch[0], rhs->ch[0]);
        lhs->ch[1] = merge(lhs->ch[1], rhs->ch[1]);
        lhs->up();
        delete rhs;
        return lhs;
      }
    } else {
      lhs->down();
      rhs->down();
      int diff_bit = 31 - __builtin_clz(lhs->bits() ^ rhs->bits());
      CompressedTrie* u = new CompressedTrie;
      u->lowest_eq_bit = diff_bit + 1;
      u->val = 0;
      u->recieve_bits(lhs->pop_bits(diff_bit + 1));
      rhs->pop_bits(diff_bit + 1);
      u->ch[testbit(lhs->bits(), diff_bit)] = lhs;
      u->ch[testbit(rhs->bits(), diff_bit)] = rhs;
      u->up();
      return u;
    }
  } else {
    if (lhs->lowest_eq_bit > rhs->lowest_eq_bit) {
      std::swap(lhs, rhs);
    }
    if ((lhs->bits() ^ rhs->bits()) >> rhs->lowest_eq_bit == 0) {
      lhs->down();
      lhs->pop_bits(rhs->lowest_eq_bit);
      rhs->down();
      int c = testbit(lhs->bits(), rhs->lowest_eq_bit - 1);
      rhs->ch[c] = merge(lhs, rhs->ch[c]);
      rhs->up();
      rhs = shrink(rhs);
      return rhs;
    } else {
      lhs->down();
      rhs->down();
      int diff_bit = 31 - __builtin_clz(lhs->bits() ^ rhs->bits());
      CompressedTrie* u = new CompressedTrie;
      u->lowest_eq_bit = diff_bit + 1;
      u->val = 0;
      u->recieve_bits(lhs->pop_bits(diff_bit + 1));
      rhs->pop_bits(diff_bit + 1);
      u->ch[testbit(lhs->bits(), diff_bit)] = lhs;
      u->ch[testbit(rhs->bits(), diff_bit)] = rhs;
      u->up();
      return u;
    }
  }
}

std::pair<CompressedTrie*, CompressedTrie*> split(CompressedTrie* trie, int k) {
  if (trie == nullptr) return {nullptr, nullptr};
  if (trie->cnt == k) return {trie, nullptr};
  if (k == 0) return {nullptr, trie};
  trie->down();
  if (trie->ch[0] == nullptr && trie->ch[1] == nullptr) {
    CHECK(trie->cnt >= k);
    CHECK(trie->lowest_eq_bit == 0);
    CompressedTrie* copy = new CompressedTrie(*trie);
    trie->cnt = k;
    trie->up();
    copy->cnt -= k;
    copy->up();
    return {trie, copy};
  } else if (trie->ch[0]->cnt >= k) {
    trie->ch[0]->recieve_bits(trie->bits());
    auto pair = split(trie->ch[0], k);
    if (pair.second) {
      pair.second->pop_bits(trie->lowest_eq_bit);
    }
    trie->ch[0] = pair.second;
    trie->up();
    trie = shrink(trie);
    return {pair.first, trie};
  } else {
    trie->ch[1]->recieve_bits(trie->bits());
    auto pair = split(trie->ch[1], k - trie->ch[0]->cnt);
    if (pair.first) {
      pair.first->pop_bits(trie->lowest_eq_bit);
    }
    trie->ch[1] = pair.first;
    trie->up();
    trie = shrink(trie);
    return {trie, pair.second};
  }
}

}  // namespace compressed_trie

namespace treap {

struct Node *nill;

struct Node {
  Node *ch[2] = {nill, nill};
  int sz = 1;

  compressed_trie::CompressedTrie* trie = nullptr;
  int trie_cnt = 0;
  unsigned s = 0;

  unsigned val = 0;
  unsigned tag = 0;

  void up() {
    if (this == nill) return;
    sz = ch[0]->sz + ch[1]->sz + 1;
    trie_cnt = 0;
    s = 0;
    if (trie) {
      trie_cnt += trie->cnt;
      s ^= trie->s;
      if (trie->cnt & 1) s ^= val;
    }
    trie_cnt += ch[0]->trie_cnt + ch[1]->trie_cnt;
    s ^= ch[0]->s ^ ch[1]->s;
  }

  void update(unsigned x) {
    if (this == nill || x == 0) return;
    if (trie_cnt & 1) s ^= x;
    if (trie) val ^= x;
    tag ^= x;
  }

  void down() {
    if (this == nill || tag == 0) return;
    ch[0]->update(tag);
    ch[1]->update(tag);
    tag = 0;
  }

  void sort() {
    if (this == nill) return;
    down();
    if (trie && val) {
      trie->update(val);
      val = 0;
    }
    CHECK(val == 0 && tag == 0);
    if (ch[0] != nill) {
      ch[0]->sort();
      trie = compressed_trie::merge(ch[0]->trie, trie);
      delete ch[0];
      ch[0] = nill;
    }
    if (ch[1] != nill) {
      ch[1]->sort();
      trie = compressed_trie::merge(trie, ch[1]->trie);
      delete ch[1];
      ch[1] = nill;
    }
    up();
  }
};

void init() {
  nill = new Node;
  nill->ch[0] = nill->ch[1] = nill;
  nill->sz = 0;
}

void split(Node* a, Node*& b, Node*& c, int trie_cnt_k) {
  if (a == nill) {
    b = c = nill;
  } else if (a->ch[0]->trie_cnt >= trie_cnt_k) {
    a->down();
    c = a;
    split(a->ch[0], b, c->ch[0], trie_cnt_k);
    c->up();
  } else if (a->ch[0]->trie_cnt + (a->trie ? a->trie->cnt : 0) < trie_cnt_k) {
    a->down();
    b = a;
    split(a->ch[1], b->ch[1], c, trie_cnt_k - a->ch[0]->trie_cnt - (a->trie ? a->trie->cnt : 0));
    b->up();
  } else if (a->ch[0]->trie_cnt + (a->trie ? a->trie->cnt : 0) == trie_cnt_k) {
    CHECK(a->trie != nullptr);
    a->down();
    c = a->ch[1];
    b = a;
    b->ch[1] = nill;
    b->up();
  } else {
    a->down();
    CHECK(trie_cnt_k > a->ch[0]->trie_cnt);
    auto pair = compressed_trie::split(a->trie, trie_cnt_k - a->ch[0]->trie_cnt);
    CHECK(pair.first != nullptr);
    CHECK(pair.second != nullptr);
    c = new Node;
    c->trie = pair.second;
    c->val = a->val;
    c->ch[1] = a->ch[1];
    c->up();
    b = a;
    b->ch[1] = nill;
    b->trie = pair.first;
    b->up();
  }
}

unsigned ran() {
  static unsigned ranx = 233233233;
  return ranx += ranx << 2 | 1;
}

bool roll(int a, int b) {
  return ran() % (a+b) < a;
}

void merge(Node*& a, Node* b ,Node* c) {
  if (b == nill) {
    a = c;
  } else if (c == nill) {
    a = b;
  } else if (roll(b->sz, c->sz)) {
    a = b;
    a->down();
    merge(a->ch[1], b->ch[1], c);
    a->up();
  } else {
    a = c;
    a->down();
    merge(a->ch[0], b, c->ch[0]);
    a->up();
  }
}

}  // namespace treap

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::istream& reader = std::cin;

  treap::init();

  int n, m;
  reader >> n >> m;

  treap::Node* tree = treap::nill;
  for (int i = 0; i < n; ++i) {
    unsigned a;
    reader >> a;
    treap::Node* u = new treap::Node;
    u->trie = new compressed_trie::CompressedTrie(a);
    u->trie_cnt = 1;
    u->s = a;
    treap::merge(tree, tree, u);
  }
  for (int i = 0; i < m; ++i) {
    int op, l, r;
    reader >> op >> l >> r;
    treap::Node* a = treap::nill;
    treap::Node* b = treap::nill;
    treap::Node* c = treap::nill;
    treap::split(tree, b, c, r);
    treap::split(b, a, b, l - 1);

    if (op == 1) {
      unsigned x;
      reader >> x;
      b->update(x);
    } else if (op == 2) {
      b->sort();
    } else {
      std::cout << (b->s) << std::endl;
    }

    treap::merge(b, a, b);
    treap::merge(tree, b, c);
  }
}

