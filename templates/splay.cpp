struct Node* nill = nullptr;

struct Node {
  Node* fa = nill;
  Node* ch[2] = {nill, nill};
  bool reverse_tag = false;

  int sz = 1;

  static void initialize() {
    if (nill == nullptr) {
      static Node nill_storage;
      nill = new(&nill_storage) Node();
      nill->sz = 0;
    }
  }

  void up() {
    if (this == nill) return;
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
    reverse_tag ^= 1;
    std::swap(ch[0], ch[1]);
  }

  bool d() const { return fa->ch[1]==this; }
  void setc(Node* o, int c) { ch[c] = o; o->fa = this; up(); }
  void rot() {
    int c = d(), cc = fa->d();
    Node* z = fa->fa;
    Node* tmp = fa;
    fa->setc(ch[c ^ 1], c);
    setc(tmp, c ^ 1);
    z->setc(this, cc);
  }
  void D() { if (fa != nill) fa->D(); down(); }

  Node* splay(Node* aim = nill) {
    for (D(); fa != aim; rot()) {
      if (fa->fa != aim) {
        d() == fa->d() ? fa->rot() : rot();
      }
    }
    return this;
  }
};
