struct Node *nill;

struct Node {
  Node* fa = nill;
  Node* ch[2] = {nill, nill};
  bool rev_tag = false;
  int val = 0, vmax = 0;
  int sz = 1, vc = 0;
  // sz   : splay子树的节点以及虚树节点和.
  // vc   : 虚树节点和.
  // vmax : splay子树最大val.

  //      : 所有修改操作只关于access后的根进行.

  Node() {}
  explicit Node(int val) : val(val), vmax(val) {}

  void up() {
    if (this == nill) return;
    vmax = std::max(val, std::max(ch[0]->vmax, ch[1]->vmax));
    sz = 1 + vc + ch[0]->sz + ch[1]->sz;
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
      p->vc += p->ch[1]->sz;
      p->vc -= q->sz;
      p->setc(q,1);
      q = p;
      p = p->fa;
    }
    return splay();
  }

  void link(Node* p) {
    p->access();
    make_root()->fa = p;
    p->vc += sz;
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

const int kN = 600000 + 5;
Node pool[kN], *node[kN], *alloc;
int n;

void lct_init() {
  alloc = pool;
  nill = new(alloc ++) Node();
  nill->fa = nill->ch[0] = nill->ch[1] = nill;
  nill->sz = 0;

  for (int i = 0; i < n; ++ i) {
    node[i] = new(alloc ++) Node();
  }
}
