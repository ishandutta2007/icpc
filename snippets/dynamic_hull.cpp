struct DynamicHull {
 public:
  using LL = long long;

  // Two operation types are supported:
  // - Insert a new line with slope equals to k and intercept equals to m.
  // - Given a param x, find the maximum value of k * x + m among lines_.

  struct Line {
    static constexpr LL inf = std::numeric_limits<LL>::max();
    LL k, m;
    mutable LL p;
    Line(LL k, LL m, LL p) : k(k), m(m), p(p) {}
    bool is_query() const { return m == inf; }
    bool operator < (const Line &rhs) const {
      if (is_query() || rhs.is_query()) return p < rhs.p;
      return k < rhs.k;
    }
  };

  void insert_line(LL k, LL m) {
    auto y = lines_.insert(Line(k, m, 0));
    for (auto z = std::next(y); isect(y, z); z = lines_.erase(z));
    if (y != lines_.begin()) {
      auto x = std::prev(y);
      if (isect(x, y)) isect(x, y = lines_.erase(y));
      while ((y = x) != lines_.begin() && (--x)->p >= y->p) isect(x, lines_.erase(y));
    }
  }

  LL eval(LL x) {
    auto line = *lines_.lower_bound(Line(0, Line::inf, x));
    return line.k * x + line.m;
  }

  bool empty() const { return lines_.empty(); }
  int size() const { return lines_.size(); }
  const std::multiset<Line>& lines() const { return lines_; }

 private:
  using iterator = std::multiset<Line>::iterator;

  LL div(LL a, LL b) {
    return a / b - ((a ^ b) < 0 && a % b);
  }
  bool isect(iterator a, iterator b) {
    if (b == lines_.end()) { a->p = Line::inf; return false; }
    if (a->k == b->k) a->p = a->m > b->m ? Line::inf : -Line::inf;
    else a->p = div(b->m - a->m, a->k - b->k);
    return a->p >= b->p;
  }

  std::multiset<Line> lines_;
};

