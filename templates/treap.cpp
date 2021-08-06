struct Treap *nill;

struct Treap {
  Treap *ch[2] = {nill, nill};
  int sz = 1;
  bool reversed = false;

  void reverse() {
    if (this == nill) return;
    std::swap(ch[0], ch[1]);
    reversed ^= 1;
  }

  void down() {
    if (this == nill) return;
    if (reversed) {
      ch[0]->reverse();
      ch[1]->reverse();
      reversed = false;
    }
  }

  void up() {
    if (this == nill) return ;
    sz = ch[0]->sz + ch[1]->sz + 1;
  }
};

void split_by_sz(Treap *a, Treap *&b, Treap *&c, int sz) {
  if (a == nill) {
    b = c = nill;
  } else if (sz == 0) {
    b = nill;
    c = a;
  } else if (a->sz == sz) {
    b = a;
    c = nill;
  } else if (a->ch[0]->sz >= sz) {
    a->down();
    c = a;
    split_by_sz(a->ch[0], b, c->ch[0], sz);
    c->up();
  } else {  // a->ch[0]->sz < sz
    a->down();
    b = a;
    split_by_sz(a->ch[1],b->ch[1], c, sz - a->ch[0]->sz - 1);
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

void merge(Treap *&a, Treap *b, Treap *c) {
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

template<typename Handler>
Handler on_interval(Handler&& handler, Treap*& root, int l, int r) {
  Treap *a, *b, *c;
  split_by_sz(root, b, c, r);
  split_by_sz(b, a, b, l - 1);
  handler(b);
  merge(b, a, b);
  merge(root, b, c);
  return handler;
}

void treap_init() {
  nill = new Treap;
  nill->ch[0] = nill->ch[1] = nill;
  nill->sz = 0;
}

