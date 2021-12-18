using LL = long long;

struct Line {
  static constexpr LL kIsQuery = -(1LL << 62);
  LL m, b;
  mutable std::function<const Line*()> succ;
  bool operator < (const Line &rhs) const {
    if (rhs.b != kIsQuery) return m < rhs.m;
    const Line* s = succ();
    if (!s) return false;
    LL x = rhs.m;
    return b - s->b < (s->m - m) * x;  // ld?
  }
};

std::string to_string(const Line& line) {
  return "Line{" + std::to_string(line.m) + ", " + std::to_string(line.b) + "}";
}

struct DynamicHull {
  // Two operation types are supported:
  // - Insert a new line with slope equals to m and intercept equals to b.
  // - Given a param x, find the maximum value of m * x + b among lines_.
 public:
  DynamicHull() = default;
  ~DynamicHull()  = default;

  void insert_line(LL m, LL b) {
    auto y = lines_.insert(Line{.m = m, .b = b});
    y->succ = [=] { return std::next(y) == lines_.end() ? nullptr : &*std::next(y); };
    if (bad(y)) {
      lines_.erase(y);
      return;
    }
    while (std::next(y) != lines_.end() && bad(std::next(y))) lines_.erase(std::next(y));
    while (y != lines_.begin() && bad(std::prev(y))) lines_.erase(std::prev(y));
  }

  LL eval(LL x) {
    auto iter = lines_.lower_bound(Line{x, Line::kIsQuery});
    assert(iter != lines_.end());
    auto l = *iter;
    return l.m * x + l.b;
  }

  bool empty() const { return lines_.empty(); }
  int size() const { return lines_.size(); }
  const std::multiset<Line>& lines() const { return lines_; }

 private:
  bool bad(std::multiset<Line>::iterator y) {
    auto z = std::next(y);
    if (y == lines_.begin()) {
      if (z == lines_.end()) return false;
      return y->m == z->m && y->b <= z->b;
    }
    auto x = std::prev(y);
    if (z == lines_.end()) return y->m == x->m && y->b <= x->b;
    return (x->b - y->b) * (z->m - y->m) >= (y->b - z->b) * (y->m - x->m);  // ld?
  }

  std::multiset<Line> lines_;

  // Disallow copy move and assign.
  DynamicHull(const DynamicHull& other) = delete;
  DynamicHull operator=(const DynamicHull& other) = delete;
  DynamicHull(DynamicHull&& other) = delete;
  DynamicHull operator=(DynamicHull&& other) = delete;
};

