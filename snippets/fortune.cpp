using DType = long double;
constexpr DType eps = 1e-12;

struct Point {
  DType x, y;
  explicit Point(DType x = 0, DType y = 0) : x(x), y(y) {}

  Point operator+(const Point& o) const { return Point(x + o.x, y + o.y); }
  Point operator-(const Point& o) const { return Point(x - o.x, y - o.y); }
  Point operator*(DType f) const { return Point(x * f, y * f); }
  Point rotated90() const { return Point(-y, x); }
  DType length() const { return hypotl(x, y); }
};

DType det(const Point& lhs, const Point& rhs) {
  return lhs.x * rhs.y - lhs.y * rhs.x;
}

bool operator<(const Point& lhs, const Point& rhs) {
  return std::make_pair(lhs.x, lhs.y) < std::make_pair(rhs.x, rhs.y);
}

// check if two vectors are collinear. It might make sense to use a
// different eps here, especially if points have integer coordinates
bool collinear(const Point& a, const Point& b) {
  return std::abs(det(a, b)) < eps;
}

// intersection point of lines ab and cd. Precondition is that they aren't collinear
Point intersection_lineline(
    const Point& a, const Point& b, const Point& c, const Point& d) {
  return a + (b - a) * (det(c - a, d - c) / det(b - a, d - c));
}

// circumcircle of points a, b, c. Precondition is that abc is a non-degenerate triangle.
Point get_circumcenter(const Point& a, Point b, Point c) {
  b = (a + b) * 0.5;
  c = (a + c) * 0.5;
  return intersection_lineline(b, b + (b - a).rotated90(), c, c + (c - a).rotated90());
}

// https://codeforces.com/blog/entry/85638
// An O(nlog(n)) algorithm of delaunay triangulation given a point set,
// which is the dual graph of the voronoi diagram.
struct Fortune {
 public:
  explicit Fortune(const std::vector<Point>& p) {
    n = p.size();
    v.resize(n);
    // Apply a random rotation to avoid coinside xs/ys.
    std::mt19937 rng(clock());
    const DType PI = std::atan2(1.0, 0.0) * 2;
    const DType angle = std::uniform_real_distribution<DType>(0.0, PI * 2)(rng);
    const DType c = std::cos(angle);
    const DType s = std::sin(angle);
    for (int i = 0; i < n; ++i) {
      v[i] = {Point(c * p[i].x - s * p[i].y, s * p[i].x + c * p[i].y), i};
    }
    std::sort(v.begin(), v.end());
  }

  // X is a value exceeding all coordinates
  void make(DType X = 1e9) {
    // insert two points that will always be in the beach line,
    // to avoid handling edge cases of an Arc being first or last
    X *= 3;
    line.insert(Arc(Point(-X, -X), Point(-X, X), -1));
    line.insert(Arc(Point(-X, X), Point(inf, inf), -1));
    // create all point events
    for (int i = 0; i < n; ++i) {
      pq.emplace(v[i].first.x, i, line.end());
    }
    ti = 0;
    valid.assign(1, false);
    while(!pq.empty()) {
      Event e = pq.top(); pq.pop();
      sweepx = e.x;
      if(e.id >= 0) {
        add_point_event(e.id);
      }else if(valid[-e.id]) {
        remove_vertex_event(e.it);
      }
    }
  }

  // The graph formed by delaunay edges.
  template<typename Edge>
  std::vector<std::vector<Edge>> build_graph() const {
    std::vector<std::vector<Edge>> graph(n);
    for (const auto& [p, q] : edges) {
      graph[p].emplace_back(Edge{.v = q});
      graph[q].emplace_back(Edge{.v = p});
    }
    return graph;
  }

 private:
  static constexpr DType inf = std::numeric_limits<DType>::max();
  static DType sweepx;  // x coordinate of sweep-line

  // an Arc on the beacah line is given implicitly by the focus p,
  // the focus q of the following Arc, and the position of the sweep-line.
  struct Arc {
    Point p;
    mutable Point q;
    int i;
    mutable int id = 0;

    Arc(Point p, Point q, int i) : p(p), q(q), i(i) {}

    // get y coordinate of intersection with following arc.
    // don't question my magic formulas
    DType gety(DType x) const {
      if(q.y == inf) return inf;
      x += eps;
      Point m = (p + q) * 0.5;
      Point dir = (p - m).rotated90();
      DType D = (x - p.x) * (x - q.x);
      return m.y + ((m.x - x) * dir.x + sqrtl(D) * dir.length()) / dir.y;
    }
    bool operator<(DType y) const {
      return gety(sweepx) < y;
    }
    bool operator<(const Arc& other) const {
      return gety(sweepx) < other.gety(sweepx);
    }
  };

  using Beach = std::multiset<Arc, std::less<>>;

  struct Event {
    DType x;  // the time of the event.

    // If id >= 0, it's a point event for index id.
    // If id < 0, it's an ID for a vertex event.
    int id;

    // if a vertex event, the iterator for the arc to be deleted.
    Beach::iterator it;

    Event(DType x, int id, Beach::iterator it) : x(x), id(id), it(it) {}

    bool operator<(const Event &e) const {
      return x > e.x;
    }
  };

  // update the remove event for the arc at position it
  void update(Beach::iterator it) {
    if(it->i == -1) return;  // doesn't correspond to a real point
    valid[-it->id] = false;  // mark existing remove event as invalid
    auto a = std::prev(it);
    if(collinear(it->q - it->p, a->p - it->p)) {
      // doesn't generate a vertex event
      return;
    }
    it->id = --ti;  // new vertex event ID
    valid.push_back(true);
    Point c = get_circumcenter(it->p, it->q, a->p);
    DType x = c.x + (c - it->p).length();
    // event is generated at time x.
    // make sure it passes the sweep-line, and that the arc truly shrinks to 0
    if(x > sweepx - eps && a->gety(x) + eps > it->gety(x)) {
      pq.push(Event(x, it->id, it));
    }
  }

  // add Delaunay edge
  void add_edge(int i, int j) {
    if(i == -1 || j == -1) return;
    edges.emplace_back(v[i].second, v[j].second);
  }

  void add_point_event(int i) {
    Point p = v[i].first;
    // find arc to split
    auto c = line.lower_bound(p.y);
    // insert new arcs. passing the following iterator gives a slight speed-up
    auto b = line.insert(c, Arc(p, c->p, i));
    auto a = line.insert(b, Arc(c->p, p, c->i));
    add_edge(i, c->i);
    update(a); update(b); update(c);
  }

  void remove_vertex_event(Beach::iterator it) {
    auto a = std::prev(it);
    auto b = std::next(it);
    line.erase(it);
    a->q = b->p;
    add_edge(a->i, b->i);
    update(a); update(b);
  }

  Beach line;
  std::vector<std::pair<Point, int>> v;  // <point, original index>
  std::priority_queue<Event> pq;
  std::vector<bool> valid;  // valid[-id] == true if the vertex event with corresponding id is valid
  int n, ti;  // number of points, next available vertex ID

 public:
  std::vector<std::pair<int, int>> edges;  // delaunay edges
};

DType Fortune::sweepx = 0.0;

