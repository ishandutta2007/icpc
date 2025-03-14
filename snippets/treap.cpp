struct Treap {
  static Treap* nill;

  Treap* ch[2] = {nill, nill};
  int sz = 1;
  bool reverse_tag = false;

  static void initialize() {
    if (nill == nullptr) {
      static Treap nill_storage;
      nill = &nill_storage;
      nill = new(&nill_storage) Treap();
      nill->sz = 0;
    }
  }

  void reverse() {
    if (this == nill) return;
    std::swap(ch[0], ch[1]);
    reverse_tag ^= 1;
  }

  void down() {
    if (this == nill) return;
    if (reverse_tag) {
      ch[0]->reverse();
      ch[1]->reverse();
      reverse_tag = false;
    }
  }

  void up() {
    if (this == nill) return ;
    sz = ch[0]->sz + ch[1]->sz + 1;
  }
};

Treap* Treap::nill = nullptr;

void split_by_sz(Treap* a, Treap*& b, Treap*& c, int sz) {
  if (a == Treap::nill) {
    b = c = Treap::nill;
  } else if (sz == 0) {
    b = Treap::nill;
    c = a;
  } else if (a->sz == sz) {
    b = a;
    c = Treap::nill;
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
  return ran() % (a + b) < a;
}

void merge(Treap*& a, Treap* b, Treap* c) {
  if (b == Treap::nill) {
    a = c;
  } else if (c == Treap::nill) {
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
  Treap* a = Treap::nill;
  Treap* b = Treap::nill;
  Treap* c = Treap::nill;
  split_by_sz(root, b, c, r);
  split_by_sz(b, a, b, l - 1);
  handler(b);
  merge(b, a, b);
  merge(root, b, c);
  return handler;
}

