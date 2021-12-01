#include <bits/stdc++.h>
#ifdef ALGO
#include "el_psy_congroo.hpp"
#else
#define DUMP(...) 1145141919810
#define CHECK(...) (__VA_ARGS__)
#endif

struct Node* nill = nullptr;

// Note: Generally speaking, all modifications should act only on the root of the splay tree after access().
struct Node {
  // Fundamental fields for splay/LCT.
  Node* fa = nill;
  Node* ch[2] = {nill, nill};
  bool rev_tag = false;

  // Node's own information.
  int val = 0;

  // Auxiliary summary.
  int vmax = 0;  // the max val among splay nodes'.
  int sz = 1;  // sum of sz of splay subtrees plus sum of sz of virtual subtrees.

  // Virtual children's summary.
  struct VirtualSummary {
    int vc = 0;  // sum of sz of virtual subtrees.
  };
  VirtualSummary virtual_summary;

  static void initialize() {
    if (nill == nullptr) {
      nill = new Node();
      nill = new(nill) Node();
    }
  }

  Node() {}
  explicit Node(int val) : val(val), vmax(val) {}

  void up() {
    if (this == nill) return;
    vmax = std::max(val, std::max(ch[0]->vmax, ch[1]->vmax));
    sz = 1 + virtual_summary.vc + ch[0]->sz + ch[1]->sz;
  }

  void down() {
    if (this == nill) return;
    if (rev_tag) {
      ch[0]->reverse();
      ch[1]->reverse();
      rev_tag = false;
    }
  }

  void reverse() {
    std::swap(ch[0],ch[1]);
    rev_tag ^= 1;
  }

  void join_as_virtual_child(VirtualSummary& virtual_summary) const {
    if (this == nill) return;
    CHECK(is_splay_root());
    virtual_summary.vc += this->sz;
  }

  void detach_from_virtual_child(VirtualSummary& virtual_summary) const {
    if (this == nill) return;
    CHECK(is_splay_root());
    virtual_summary.vc -= this->sz;
  }

  bool d() const { return fa->ch[1] == this; }
  bool is_splay_root() const { return fa == nill || (fa->ch[0] != this && fa->ch[1] != this); }
  void D() { if (!is_splay_root()) fa->D(); down(); }
  void setc(Node* o, int c) { ch[c] = o; o->fa = this; up(); }

  void rot() {
    int c = d(), cc = fa->d();
    Node* ff = fa->fa;
    Node* f = fa;
    f->setc(ch[c ^ 1], c);
    this->setc(f, c ^ 1);
    if (ff->ch[cc] == f) ff->setc(this, cc);
    else this->fa = ff;
  }

  Node* splay() {
    for (D(); !is_splay_root(); rot()) {
      if (!fa->is_splay_root())
        d() == fa->d() ? fa->rot() : rot();
    }
    return this;
  }

  Node* access() {
    for (Node *p = this, *q = nill; p != nill; ) {
      p->splay();
      p->ch[1]->join_as_virtual_child(p->virtual_summary);
      q->detach_from_virtual_child(p->virtual_summary);
      p->setc(q,1);
      q = p;
      p = p->fa;
    }
    return splay();
  }

  void link(Node* parent) {
    parent->access();
    make_root()->fa = parent;
    join_as_virtual_child(parent->virtual_summary);
    parent->up();
  }

  Node* cut() {
    access();
    Node* parent = get_splay_precursor()->access();
    detach_from_virtual_child(parent->virtual_summary);
    fa = nill;
    parent->up();
    return parent;
  }

  Node* make_root() {
    access()->reverse();
    down();
    return this;
  }

  Node* get_splay_precursor() {
    this->down();
    Node* p = this->ch[0];
    CHECK(p != nill);
    while (true) {
      p->down();
      if (p->ch[1] == nill) break;
      p = p->ch[1];
    }
    return p;
  }

  Node* get_max() {
    Node* p = this;
    while (true) {
      p->down();
      if (p->val >= p->ch[0]->vmax && p->val >= p->ch[1]->vmax) {
        return p;
      }
      if (p->ch[0]->vmax >= p->ch[1]->vmax) {
        p = p->ch[0];
      } else {
        p = p->ch[1];
      }
    }
  }
};

const int kN = 300000 + 5;
Node pool[kN], *node[kN], *alloc;
int n;

void lct_init() {
  alloc = pool;
  nill = new(alloc++) Node();
  nill->fa = nill->ch[0] = nill->ch[1] = nill;
  nill->sz = 0;

  for (int i = 0; i < n; ++ i) {
    node[i] = new(alloc++) Node();
  }
}
