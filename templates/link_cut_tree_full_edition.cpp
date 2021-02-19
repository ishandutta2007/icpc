#include <bits/stdc++.h>
#ifdef ALGO
#include "el_psy_congroo.hpp"
#else
#define DUMP(...) 1145141919810
#define CHECK(...) (__VA_ARGS__)
#endif

// FIXME: Under construction.
struct Node *nill;

struct Node {
  Node* fa = nill;
  Node* ch[2] = {nill, nill};
  bool rev_tag = false;

  struct Summary {
    int val = 0;

    int sz = 1;  // sum of subtree size of virtual children plus sum of sz in the splay tree.
    int vmax = 0;  // max val among val in the splay tree.

    Summary() {}
    explicit Summary(int val) : val(val), vmax(val) {}
  };

  struct VirtualSummary {
    int vc = 0;  // total size in virtual children's subtrees.

    void add(const Summary& A) {
      vc += A.sz;
    }

    void subtract(const Summary& A) {
      vc -= A.sz;
    }
  };

  void recalculate(Summary& A,
                   const VirtualSummary& O,
                   const Summary& left,
                   const Summary& right) {
    A.sz = 1 + O.vc + left.sz + right.sz;
    A.vmax = std::max(A.val, std::max(left.vmax, right.vmax));
  }

  Summary summary;
  VirtualSummary virtual_summary;

  Node() {}
  explicit Node(int val) : summary(val) {}

  void up() {
    if (this == nill) return;
    recalculate(summary, virtual_summary, ch[0]->summary, ch[1]->summary);
  }

  void down() {
    if (this == nill) return;
    if (rev_tag) {
      rev_tag = false;
      ch[0]->rev();
      ch[1]->rev();
    }
  }

  void rev() {
    std::swap(ch[0],ch[1]);
    rev_tag ^= 1;
  }

  bool d() const { return fa->ch[1] == this; }
  bool isroot() const { return fa == nill || (fa->ch[0] != this && fa->ch[1] != this); }
  void D() { if (!isroot()) fa->D(); down(); }
  void setc(Node *p, int c) { ch[c] = p; p->fa = this; up(); }

  void rot() {
    Node *f = fa, *ff = fa->fa;
    int c = d(), cc = fa->d();
    f->setc(ch[c ^ 1], c);
    this->setc(f, c ^ 1);
    if (ff->ch[cc] == f) ff->setc(this, cc);
    else this->fa = ff;
  }

  Node* splay() {
    for (D(); !isroot(); rot()) {
      if (!fa->isroot())
        d() == fa->d() ? fa->rot() : rot();
    }
    return this;
  }

  Node* access() {
    for (Node *p = this, *q = nill; p != nill; ) {
      p->splay();
      p->virtual_summary.subtract(q->summary);
      p->virtual_summary.add(p->ch[1]->summary);
      p->setc(q,1);
      q = p;
      p = p->fa;
    }
    return splay();
  }

  void link(Node* p) {
    p->access();
    make_root()->fa = p;
    p->virtual_summary.add(this->summary);
    p->up();
  }

  Node* make_root() {
    access()->rev();
    down();
    return this;
  }

  Node* get_max() {
    Node* p = this;
    while (true) {
      p->down();
      if (p->summary.val >= p->ch[0]->summary.vmax && p->summary.val >= p->ch[1]->summary.vmax) {
        return p;
      }
      if (p->ch[0]->summary.vmax >= p->ch[1]->summary.vmax) {
        p = p->ch[0];
      } else {
        p = p->ch[1];
      }
    }
  }
};

const int kN = 600000 + 5;
Node pool[kN], *node[kN], *alloc;
int n;

void lct_init() {
  alloc = pool;
  nill = new(alloc ++) Node();
  nill->fa = nill->ch[0] = nill->ch[1] = nill;
  nill->summary.sz = 0;

  for (int i = 0; i < n; ++ i) {
    node[i] = new(alloc ++) Node();
  }
}
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::istream& reader = std::cin;
}

