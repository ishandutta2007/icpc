struct SuffixAutomaton {
  static constexpr int kCharsetSize = 26;
  static int hash(char c) { return c - 'a'; }

  SuffixAutomaton() {
    root = allocate(0);
    last = allocate(1);
    last->fa = root;
  }
  explicit SuffixAutomaton(const std::string& str) : SuffixAutomaton() {
    for (int i = 0; i < str.length(); ++i) extend(hash(str[i]));
  }

  struct Node {
    Node* fa = nullptr;
    std::array<Node*, kCharsetSize> go = {nullptr};
    int val = 0;
    int id = -1;

    explicit Node(int val = 0) : val(val) {}
  };

  template<typename... Args>
  static Node* allocate(Args&&... args) {
    Node* u = pool.allocate(std::forward<Args>(args)...);
    return u;
  }

  static MemoryPool<Node> pool;

  Node* root = nullptr;
  Node* last = nullptr;

  void extend(int c) {
    Node* p = last;
    Node* np = allocate(p->val + 1);
    while (p && p->go[c] == 0) {
      p->go[c] = np; p = p->fa;
    }
    if (p == 0) {
      np->fa = root;
    } else {
      Node* q = p->go[c];
      if (p->val + 1 == q->val) {
        np->fa = q;
      } else {
        Node* nq = allocate(p->val + 1);
        std::copy(q->go.begin(), q->go.end(), nq->go.begin());
        nq->fa = q->fa;
        q->fa = nq;
        np->fa = nq;
        while (p && p->go[c] == q) {
          p->go[c] = nq;
          p = p->fa;
        }
      }
    }
    last = np;
  }

  bool is_substr(const std::string& str) const {
    Node* u = root;
    for (char c : str) {
      u = u->go[hash(c)];
      if (u == nullptr) return false;
    }
    return true;
  }
};

MemoryPool<SuffixAutomaton::Node> SuffixAutomaton::pool;

