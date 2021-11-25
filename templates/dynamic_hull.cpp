using LL = long long;

struct Line {
  static constexpr LL kIsQuery = -(1LL << 62);
  LL m, b;
  mutable std::function<const Line* ()> succ;
  bool operator < (const Line &rhs) const {
    if (rhs.b != kIsQuery) return m < rhs.m;
    const Line *s = succ();
    if (!s) return false;
    LL x = rhs.m;
    return b - s->b < (s->m - m) * x;  // ld?
  }
};

std::string to_string(const Line& line) {
  return "Line{" + std::to_string(line.m) + ", " + std::to_string(line.b) + "}";
}

struct DynamicHull : public std::multiset<Line> {
  // Maintain an upper side convex hull of lines.
  // Two operation types are supported:
  // - Insert a new line with slope equals to m and intercept equals to b.
  // - Given a param x, find the maximum value of m * x + b among lines.
 public:
  void insert_line(LL m, LL b) {
    auto y = insert({m, b});
    y->succ = [=] { return next(y) == end() ? nullptr : &*next(y); };
    if (bad(y)) {
      erase(y);
      return;
    }
    while (next(y) != end() && bad(next(y))) erase(next(y));
    while (y != begin() && bad(prev(y))) erase(prev(y));
  }

  LL eval(LL x) {
    auto l = *lower_bound(Line{x, Line::kIsQuery});
    return l.m * x + l.b;
  }

 private:
  bool bad(iterator y) {
    auto z = next(y);
    if (y == begin()) {
      if (z == end()) return false;
      return y->m == z->m && y->b <= z->b;
    }
    auto x = prev(y);
    if (z == end()) return y->m == x->m && y->b <= x->b;
    return (x->b - y->b) * (z->m - y->m) >= (y->b - z->b) * (y->m - x->m);  // ld?
  }
};

