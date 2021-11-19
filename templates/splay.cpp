struct Node *nill;

struct Node {
  Node* ch[2] = {nill, nill};
  Node* fa = nill;
  int sz = 0;
  bool rev = false;

  void up() {
    if (this == nill) return;
    sz = ch[0]->sz + ch[1]->sz + 1;
  }

  void down() {
    if (this == nill) return;
    if (!rev) return;
    rev = false;
    ch[0]->reverse();
    ch[1]->reverse();
  }

  bool d() const { return fa->ch[1]==this; }
  void reverse() {
    rev ^= 1;
    std::swap(ch[0], ch[1]);
  }
  void setc(Node* o, int c) {
    ch[c] = o;
    o->fa = this;
    up();
  }
  void rot() {
    int c = d(), cc = fa->d();
    Node* z = fa->fa;
    Node* tmp = fa;
    fa->setc(ch[c ^ 1], c);
    setc(tmp, c ^ 1);
    z->setc(this, cc);
  }
  void D() {
    if (this == nill) return;
    fa->D();
    down();
  }
  void splay(Node* aim = nill) {
    D();
    while (fa != aim) {
      if (fa->fa != aim) {
        d()==fa->d() ? fa->rot() : rot();
      }
      rot();
    }
  }
};
