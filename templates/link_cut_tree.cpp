// Note: Generally speaking, all modifications should act only on the root of the splay tree after access().
struct LinkCutTree {
  static LinkCutTree* nill;

  // Fundamental fields for splay/LCT.
  LinkCutTree* fa = nill;
  LinkCutTree* ch[2] = {nill, nill};
  bool reverse_tag = false;

  // The owned information of the LCT node.
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
      static LinkCutTree nill_storage;
      nill = &nill_storage;
      nill = new(&nill_storage) LinkCutTree();
      nill->sz = 0;
    }
  }

  LinkCutTree() {}
  explicit LinkCutTree(int val) : val(val), vmax(val) {}

  void up() {
    if (this == nill) return;
    down();  // In case children's order matter.
    vmax = std::max(val, std::max(ch[0]->vmax, ch[1]->vmax));
    sz = 1 + virtual_summary.vc + ch[0]->sz + ch[1]->sz;
  }

  void down() {
    if (this == nill) return;
    if (reverse_tag) {
      ch[0]->reverse();
      ch[1]->reverse();
      reverse_tag = false;
    }
  }

  void reverse() {
    if (this == nill) return;
    std::swap(ch[0],ch[1]);
    reverse_tag ^= 1;
  }

  void join_as_virtual_child(VirtualSummary& virtual_summary) const {
    if (this == nill) return;
    assert(is_splay_root());
    virtual_summary.vc += this->sz;
  }

  void detach_from_virtual_child(VirtualSummary& virtual_summary) const {
    if (this == nill) return;
    assert(is_splay_root());
    virtual_summary.vc -= this->sz;
  }

  bool d() const { return fa->ch[1] == this; }
  bool is_splay_root() const { return fa == nill || (fa->ch[0] != this && fa->ch[1] != this); }
  void D() { if (!is_splay_root()) fa->D(); down(); }
  void setc(LinkCutTree* o, int c) {
    if (this != nill) ch[c] = o;
    if (o != nill) o->fa = this;
    up();
  }

  void rot() {
    int c = d(), cc = fa->d();
    LinkCutTree* ff = fa->fa;
    LinkCutTree* f = fa;
    f->setc(ch[c ^ 1], c);
    this->setc(f, c ^ 1);
    if (ff->ch[cc] == f) ff->setc(this, cc);
    else this->fa = ff;
  }

  LinkCutTree* splay() {
    for (D(); !is_splay_root(); rot()) {
      if (!fa->is_splay_root())
        d() == fa->d() ? fa->rot() : rot();
    }
    return this;
  }

  LinkCutTree* access() {
    for (LinkCutTree *p = this, *q = nill; p != nill; ) {
      p->splay();
      q->detach_from_virtual_child(p->virtual_summary);
      LinkCutTree* r = p->ch[1];
      p->setc(q, 1);
      r->join_as_virtual_child(p->virtual_summary);
      p->up();
      q = p;
      p = p->fa;
    }
    return splay();
  }

  void link(LinkCutTree* parent) {
    parent->access();
    make_root()->fa = parent;
    join_as_virtual_child(parent->virtual_summary);
    parent->up();
  }

  LinkCutTree* cut() {
    access();
    LinkCutTree* parent = get_splay_precursor()->access();
    detach_from_virtual_child(parent->virtual_summary);
    fa = nill;
    parent->up();
    return parent;
  }

  LinkCutTree* make_root() {
    access()->reverse();
    down();
    return this;
  }

  LinkCutTree* get_splay_precursor() {
    this->down();
    LinkCutTree* p = this->ch[0];
    if (p == nill) return nill;
    while (true) {
      p->down();
      if (p->ch[1] == nill) break;
      p = p->ch[1];
    }
    return p;
  }

  LinkCutTree* get_max() {
    LinkCutTree* p = this;
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

LinkCutTree* LinkCutTree::nill = nullptr;

