struct Splay {
  static Splay* nill;

  Splay* fa = nill;
  Splay* ch[2] = {nill, nill};
  bool reverse_tag = false;

  int sz = 1;

  static void initialize() {
    if (nill == nullptr) {
      static Splay nill_storage;
      nill = &nill_storage;
      nill = new(&nill_storage) Splay();
      nill->sz = 0;
    }
  }

  void up() {
    if (this == nill) return;
    down();  // In case children's order matter.
    sz = ch[0]->sz + ch[1]->sz + 1;
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
    reverse_tag ^= 1;
    std::swap(ch[0], ch[1]);
  }

  bool d() const { return fa->ch[1] == this; }
  void setc(Splay* o, int c) {
    if (this != nill) ch[c] = o;
    if (o != nill) o->fa = this;
    up();
  }
  void rot() {
    int c = d(), cc = fa->d();
    Splay* z = fa->fa;
    Splay* tmp = fa;
    fa->setc(ch[c ^ 1], c);
    setc(tmp, c ^ 1);
    z->setc(this, cc);
  }
  void D() { if (fa != nill) fa->D(); down(); }

  Splay* splay(Splay* aim = nill) {
    if (this == nill) return this;
    for (D(); fa != aim; rot()) {
      if (fa->fa != aim) {
        d() == fa->d() ? fa->rot() : rot();
      }
    }
    return this;
  }

  Splay* get_kth(int k) {
    if (this == nill || k <= 0 || k > this->sz) return nill;
    Splay* v = this;
    while (true) {
      v->down();
      if (v->ch[0]->sz >= k) v = v->ch[0];
      else if (v->ch[0]->sz + 1 == k) return v;
      else k -= v->ch[0]->sz + 1, v = v->ch[1];
    }
  }
};

Splay* Splay::nill = nullptr;

