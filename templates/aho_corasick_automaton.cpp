struct Trie {
  static int charset_size;

  Trie() : go(charset_size) {}

  Trie* fail = nullptr;
  std::vector<Trie*> go;

  int id = -1;

  // OnLinkFail :: void(Trie* u, Trie* fail)
  // NOTE: u may equals to fail.
  template<typename OnLinkFail>
  void build_fails(OnLinkFail&& on_link_fail) {
    Trie* root = this;
    root->fail = root;
    on_link_fail(root, root);
    std::queue<Trie*> que;
    que.emplace(root);
    while (!que.empty()) {
      Trie* u = que.front(); que.pop();
      for (int ch = 0; ch < charset_size; ++ch) if (u->go[ch] != nullptr) {
        Trie* v = u->go[ch];
        Trie* f = u->fail;
        while (f != root && f->go[ch] == nullptr) f = f->fail;
        v->fail = f->go[ch] == nullptr || f->go[ch] == v ? f : f->go[ch];
        on_link_fail(v, v->fail);
        que.emplace(v);
      }
    }
  }
};

int Trie::charset_size = 26;

