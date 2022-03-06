struct Trie {
  constexpr static int kCharsetSize = 26;

  Trie* fail = nullptr;
  std::array<Trie*, kCharsetSize> go;

  // OnLinkFail :: void(Trie* u, Trie* fail).
  // NOTE: u may equals to fail.
  template<typename OnLinkFail = std::function<void(Trie*,Trie*)>>
  void build_fails(OnLinkFail&& on_link_fail = [](Trie*, Trie*){}) {
    Trie* root = this;
    root->fail = root;
    on_link_fail(root, root);
    std::queue<Trie*> que;
    que.emplace(root);
    while (!que.empty()) {
      Trie* u = que.front(); que.pop();
      for (int ch = 0; ch < kCharsetSize; ++ch) if (u->go[ch] != nullptr) {
        Trie* v = u->go[ch];
        Trie* f = u->fail;
        while (f != root && f->go[ch] == nullptr) f = f->fail;
        v->fail = f->go[ch] == nullptr || f->go[ch] == v ? f : f->go[ch];
        on_link_fail(v, v->fail);
        que.emplace(v);
      }
    }
  }

  void make_shortcuts() {
    Trie* root = this;
    std::queue<Trie*> que;
    que.emplace(root);
    while (!que.empty()) {
      Trie* u = que.front(); que.pop();
      for (int ch = 0; ch < kCharsetSize; ++ch) if (u->go[ch] != nullptr) {
        que.emplace(u->go[ch]);
      }
      for (int ch = 0; ch < kCharsetSize; ++ch) if (u->go[ch] == nullptr) {
        Trie* f = u->fail;
        while (f != root && f->go[ch] == nullptr) f = f->fail;
        u->go[ch] = f->go[ch] == nullptr ? root : f->go[ch];
      }
    }
  }
};

