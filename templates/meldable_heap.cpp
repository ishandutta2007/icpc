template<typename T, typename Comparator = std::less<T>>
struct MeldableHeap {
 public:
  MeldableHeap() = default;
  ~MeldableHeap() { release(root_); }

  int size() const { return size_; }
  bool empty() const { return root_ == nullptr || size() == 0; }

  T pop() {
    assert(!empty());
    Node* v = merge(root_->lc, root_->rc);
    T ret = root_->val;
    delete root_;
    root_ = v;
    --size_;
    return ret;
  }

  void insert(T val) {
    ++size_;
    Node* v = new Node;
    v->val = val;
    root_ = merge(root_, v);
  }

  void merge_from(MeldableHeap& other) {
    root_ = merge(root_, other.root_);
    size_ += other.size();
    other.size_ = 0;
    other.root_ = nullptr;
  }

 private:
  struct Node {
    int length = 1;
    T val{};
    Node* lc = nullptr;
    Node* rc = nullptr;
  };

  Node* merge(Node* u, Node* v) {
    if (u == nullptr) return v;
    if (v == nullptr) return u;
    if (!cmp_(u->val, v->val)) std::swap(u, v);
    u->rc = merge(u->rc, v);
    if (get_length(u->lc) < get_length(u->rc)) std::swap(u->lc, u->rc);
    u->length = get_length(u->lc) + 1;
    return u;
  }

  void release(Node* u) {
    if (u == nullptr) return;
    release(u->lc);
    release(u->rc);
    delete u;
  }

  int get_length(Node* u) const { return u == nullptr ? 0 : u->length; }

  Node* root_ = nullptr;
  int size_ = 0;
  Comparator cmp_;
};

