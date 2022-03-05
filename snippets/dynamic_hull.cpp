template<typename T>
struct DynamicHull {
 public:
  // Two operation types are supported:
  // - Insert a new line with slope equals to k and intercept equals to m.
  // - Given a param x, find the maximum value of k * x + m among lines_.
  //
  // Note:
  // If you want to eval in floating type, use a floating type instance directly.
  // The integral type instance may skip some lines
  // if they only dominate an interval that does not contain an integer.

  struct Line {
    static constexpr T inf = std::numeric_limits<T>::max();
    T k, m;
    mutable T p;
    Line(T k, T m, T p) : k(k), m(m), p(p) {}
    bool is_query() const { return m == inf; }
    bool operator < (const Line &rhs) const {
      if (is_query() || rhs.is_query()) return p < rhs.p;
      return k < rhs.k;
    }
  };

  void insert_line(T k, T m) {
    auto y = lines_.insert(Line(k, m, 0));
    for (auto z = std::next(y); isect(y, z); z = lines_.erase(z));
    if (y != lines_.begin()) {
      auto x = std::prev(y);
      if (isect(x, y)) isect(x, y = lines_.erase(y));
      while ((y = x) != lines_.begin() && (--x)->p >= y->p) isect(x, lines_.erase(y));
    }
  }

  T eval(T x) const {
    auto line = *lines_.lower_bound(Line(0, Line::inf, x));
    return line.k * x + line.m;
  }

  bool empty() const { return lines_.empty(); }
  int size() const { return lines_.size(); }
  const std::multiset<Line>& lines() const { return lines_; }

 private:
  using iterator = typename std::multiset<Line>::iterator;

  T div(T a, T b) const {
    if constexpr(std::is_integral<T>::value) {
      return a / b - ((a ^ b) < 0 && a % b);
    } else {
      return a / b;
    }
  }
  bool isect(iterator a, iterator b) const {
    if (b == lines_.end()) { a->p = Line::inf; return false; }
    if (a->k == b->k) a->p = a->m > b->m ? Line::inf : -Line::inf;
    else a->p = div(b->m - a->m, a->k - b->k);
    return a->p >= b->p;
  }

  std::multiset<Line> lines_;
};

