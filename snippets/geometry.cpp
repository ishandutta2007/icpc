const double eps = 1e-8;

template<typename T> inline int cmpT(T x) { return x < 0 ? -1 : x > 0; }
template<> inline int cmpT(float x) { return x < -eps ? -1 : x > eps; }
template<> inline int cmpT(double x) { return x < -eps ? -1 : x > eps; }
template<> inline int cmpT(long double x) { return x < -eps ? -1 : x > eps; }

template<typename T>
struct VecT {
  union {
    struct {
      T x;
      T y;
    };
    T elements[2] = {};
  };

  static_assert(std::is_arithmetic<T>::value, "T should be an arithmetic type.");

  VecT() = default;
  VecT(T x, T y) : x(x), y(y) {}
  ~VecT() = default;

  const T& operator[](int index) const { return elements[index]; }
  T& operator[](int index) { return elements[index]; }

  T length_sqr() const { return x * x + y * y; }

  VecT rotated90() const { return VecT(-y, x); }
  void rotate90() { *this = rotated90(); }

  double length() const { return hypot(x, y); }
  VecT<std::common_type_t<T, double>> rotated(double angle) const {
    const double c = cos(angle), s = sin(angle);
    return VecT<std::common_type_t<T, double>>(x * c - y * s, x * s + y * c);
  }
  void rotate(double angle) { *this = rotated(angle); }
  template<typename U> VecT<U> converted() const { return VecT<U>(x, y); }

  VecT& operator+=(const VecT& other) { x += other.x; y += other.y; return *this; }
  VecT operator+(const VecT& other) const { VecT ret = *this; return ret += other; }

  VecT& operator-=(const VecT& other) { x -= other.x; y -= other.y; return *this; }
  VecT operator-(const VecT& other) const { VecT ret = *this; return ret -= other; }

  VecT& operator*=(T scale) { x *= scale; y *= scale; return *this; }
  template<typename Scalar>
  VecT<std::common_type_t<T, Scalar>> operator*(Scalar scale) const {
    return converted<std::common_type_t<T, Scalar>>() *= scale;
  }

  VecT& operator/=(T scale) { assert(scale > 0); return (*this) *= T(1) / scale; }
  template<typename Scalar>
  VecT<std::common_type_t<T, Scalar>> operator/(Scalar scale) const {
    return converted<std::common_type_t<T, Scalar>>() /= scale;
  }

  bool operator<(const VecT& other) const {
    if (cmpT(x - other.x) == 0) return cmpT(y - other.y) < 0;
    return cmpT(x - other.x) < 0;
  }
  bool operator>(const VecT& other) const { return other < (*this); }
  bool operator==(const VecT& other) const { return cmpT(x - other.x) == 0 && cmpT(y - other.y) == 0; }
  bool operator!=(const VecT& other) const { return !((*this) == other); }
};

template<typename T, typename Scalar>
inline VecT<std::common_type_t<T, Scalar>> operator*(Scalar scale, const VecT<T>& v) { return v * scale; }

template<typename T>
VecT<std::common_type_t<T, double>> lerp(const VecT<T>& start, const VecT<T>& end, double ratio) {
  return VecT<std::common_type_t<T, double>>(start.x + (end.x - start.x) * ratio, start.y + (end.y - start.y) * ratio);
}

template<typename T>
std::string to_string(const VecT<T>& v) {
  return std::string("VecT{x=") + std::to_string(v.x) + ",y=" + std::to_string(v.y) + "}";
}

template<typename T> T det(const VecT<T>& a, const VecT<T>& b) { return a.x * b.y - a.y * b.x; }
template<typename T> T dot(const VecT<T>& a, const VecT<T>& b) { return a.x * b.x + a.y * b.y; }

template<typename T> using PointT = VecT<T>;
template<typename T> using PolygonT = std::vector<PointT<T>>;

template<typename T>
bool polar_cmp(const VecT<T>& a, const VecT<T>& b) {
  if (cmpT(a.y) * cmpT(b.y) <= 0) {
    if (cmpT(a.y) > 0 || cmpT(b.y) > 0) return cmpT(a.y - b.y) < 0;
    if (cmpT(a.y) == 0 && cmpT(b.y) == 0) return cmpT(a.x - b.x) < 0;
  }
  return cmpT(det(a,b)) > 0;
}

template<typename T>
bool on_point_line(const PointT<T>& p, const PointT<T>& a1, const PointT<T>& a2) {
  return cmpT(det(a1 - p, a2 - p)) == 0;
}

template<typename T>
bool has_intersection_line_line(
    const PointT<T>& p, const PointT<T>& pp, const PointT<T>& q, const PointT<T>& qq) {
  return cmpT(det(pp - p, qq - q)) != 0 || on_point_line(p, q, qq);
}

template<typename T, typename R = std::common_type_t<T, double>>
PointT<R> intersection_line_line(
    const PointT<T>& p, const PointT<T>& pp, const PointT<T>& q, const PointT<T>& qq) {
  const VecT<T> u = p - q, v = pp - p, w = qq - q;
  const T dom = det(v, w);
  if (cmpT(dom) == 0) return PointT<R>(p.x, p.y);  // collinear.
  const R ratio = det(w, u) / static_cast<R>(dom);
  return PointT<R>(p.x + v.x * ratio, p.y + v.y * ratio);
}

template<typename T, typename R = std::common_type_t<T, double>>
PointT<std::common_type_t<T, double>> projection_point_line(const PointT<T>& p, const PointT<T>& a, const PointT<T>& b) {
  const VecT<T> v = b - a;
  const R ratio = dot(v, p - a) / static_cast<R>(dot(v, v));
  return PointT<R>(a.x + v.x * ratio, a.y + v.y * ratio);
}

template<typename T>
double distance_point_line(const PointT<T>& p, const PointT<T>& a, const PointT<T>& b) {
  const VecT<T> v1 = b - a, v2 = p - a;
  return std::abs(det(v1, v2)) / v1.length();
}

template<typename T>
double distance_point_segment(const PointT<T>& p, const PointT<T>& a, const PointT<T>& b) {
  if (a == b) return (p - a).length();
  const VecT<T> v1 = b - a, v2 = p - a, v3 = p - b;
  if (cmpT(dot(v1, v2)) < 0) return v2.length();
  else if (cmpT(dot(v1, v3)) > 0) return v3.length();
  else return std::abs(det(v1, v2)) / v1.length();
}

template<typename T>
bool has_proper_intersection_segment_segment(
    const PointT<T>& a1, const PointT<T>& a2, const PointT<T>& b1, const PointT<T>& b2) {
  T c1 = det(a2 - a1, b1 - a1),
    c2 = det(a2 - a1, b2 - a1),
    c3 = det(b2 - b1, a1 - b1),
    c4 = det(b2 - b1, a2 - b1);
  return cmpT(c1) * cmpT(c2) < 0 && cmpT(c3) * cmpT(c4) < 0;
}

// End point counts.
template<typename T>
bool on_point_segment(const PointT<T>& p, const PointT<T>& a1, const PointT<T>& a2) {
  return cmpT(det(a1 - p, a2 - p)) == 0 && cmpT(dot(a1 - p, a2 - p)) <= 0;
}

// End point counts.
template<typename T>
bool has_intersection_segment_segment(
    const PointT<T>& a1, const PointT<T>& a2, const PointT<T>& b1, const PointT<T>& b2) {
  if (has_proper_intersection_segment_segment(a1, a2, b1, b2)) return true;
  return
    on_point_segment(a1, b1, b2) || on_point_segment(a2, b1, b2) ||
    on_point_segment(b1, a1, a2) || on_point_segment(b2, a1, a2);
}

template<typename T>
bool in_point_polygon(const PointT<T>& o, const PolygonT<T>& poly, bool flag) {
  // flag == true means boundary counts as inner side.
  int t = 0;
  PointT<T> a, b;
  const int n = poly.size();
  for (int i = 0; i < n; ++ i) if (on_point_segment(o, poly[i], poly[(i + 1) % n])) return flag;
  for (int i = 0; i < n; ++ i) {
    a = poly[i];
    b = poly[(i + 1) % n];
    if (cmpT(a.y - b.y) > 0) std::swap(a, b);
    if (cmpT(det(a - o, b - o)) < 0 && cmpT(a.y - o.y) < 0 && cmpT(o.y - b.y) <= 0) ++t;
  }
  return t & 1;
}

template<typename T>
std::vector<std::array<int, 3>> triangulate(const PolygonT<T>& polygon) {
  // Based on the two ears theorem.
  // Non-convex polygons are supported.
  // O(nm), where n is the number of points, and m is the number of concave points.
  const int n = polygon.size();
  std::vector<int> prev(n), next(n);
  T area = 0;
  for (int i = 0; i < n; ++i) {
    prev[i] = (i + n - 1) % n;
    next[i] = (i + 1) % n;
    area += det(polygon[i], polygon[next[i]]);
  }
  auto same_sign = [&](int i, int target_sign) -> bool {
    const int j = next[i];
    const int k = prev[i];
    const T triangle_area = det(polygon[j] - polygon[i], polygon[k] - polygon[i]);
    return cmpT(triangle_area) == target_sign;
  };
  const int area_sign = cmpT(area);
  std::set<int> concave_ids;
  std::vector<int> stack;
  for (int i = 0; i < n; ++i) {
    if (same_sign(i, -area_sign)) concave_ids.emplace(i);
    else if (same_sign(i, area_sign)) stack.emplace_back(i);
  }
  std::vector<std::array<int, 3>> result;
  std::vector<bool> del(n);
  while (!stack.empty()) {
    const int i = stack.back(); stack.pop_back();
    if (del[i] || n - (int)result.size() < 3) continue;
    assert(same_sign(i, area_sign));
    const int j = next[i];
    const int k = prev[i];
    auto inside = [&](int r) -> bool {
      const int a = cmpT(det(polygon[i] - polygon[r], polygon[j] - polygon[r]));
      const int b = cmpT(det(polygon[j] - polygon[r], polygon[k] - polygon[r]));
      const int c = cmpT(det(polygon[k] - polygon[r], polygon[i] - polygon[r]));
      return a * area_sign >= 0 && b * area_sign >= 0 && c * area_sign >= 0;
    };
    bool is_ear = true;
    for (int r : concave_ids) if (r != j && r != k) {
      is_ear &= !inside(r);
      if (!is_ear) break;
    }
    if (is_ear) {
      result.emplace_back(std::array<int, 3>{i, j, k});
      del[i] = true;
      prev[j] = k;
      next[k] = j;
      if (same_sign(j, area_sign)) {
        concave_ids.erase(j);
        stack.emplace_back(j);
      }
      if (same_sign(k, area_sign)) {
        concave_ids.erase(k);
        stack.emplace_back(k);
      }
    }
  }
  return result;
}

using Vector = VecT<double>;
using Point = Vector;
using Polygon = std::vector<Point>;

inline int dcmp(double x) { return cmpT(x); }

void geom_test() {
  CHECK(has_intersection_line_line(PointT<int>(1, 0), PointT<int>(0, 1), \
                                   PointT<int>(0, 0), PointT<int>(1, 1)));
  CHECK(has_intersection_line_line(PointT<int>(0, 0), PointT<int>(1, 1), \
                                   PointT<int>(8, 8), PointT<int>(9, 9)));
  CHECK(!has_intersection_line_line(PointT<int>(0, 0), PointT<int>(1, 1), \
                                    PointT<int>(8, 0), PointT<int>(9, 1)));
  CHECK(PointT<double>(0.5, 0.5) ==
        intersection_line_line(PointT<int>(1, 0), PointT<int>(0, 1), \
                               PointT<int>(0, 0), PointT<int>(1, 1)));
  DUMP(projection_point_line(PointT<int>(1, 1), PointT<int>(0, 0), PointT<int>(3, -2)));
  DUMP(distance_point_segment(PointT<int>(1, 1), PointT<int>(9, -7), PointT<int>(3, -2)));
  DUMP(distance_point_line(PointT<int>(1, 1), PointT<int>(9, -7), PointT<int>(3, -2)));
  CHECK(has_intersection_segment_segment(PointT<int>(1, 0), PointT<int>(0, 1), PointT<int>(0, 1), PointT<int>(1, 2)));
  CHECK(!has_proper_intersection_segment_segment(PointT<int>(1, 0), PointT<int>(0, 1), PointT<int>(0, 1), PointT<int>(1, 2)));
  CHECK(has_proper_intersection_segment_segment(PointT<int>(1, 0), PointT<int>(0, 1), PointT<int>(0, 0), PointT<int>(1, 2)));
  DUMP(PointT<int>(1, 1).rotated90());
  DUMP(PointT<int>(1, 1).rotated(1.57));
  DUMP(PointT<int>(1, 1).rotated(M_PI / 2));
  DUMP(PointT<long long>(1, 10000).converted<double>());
  DUMP(PointT<double>(1.7, -1.7).converted<int>());
  DUMP(PointT<int>(2, 3) * 1.0);
  DUMP(PointT<double>(2.1, 3.1) * 1);
  DUMP(1.0 * PointT<double>(2.1, 3.1));
  PointT<double> p(2.1, 3.1);
  p *= 5;
  CHECK(p == PointT<double>(10.5, 15.5));
  p /= 5;
  CHECK(PointT<double>(1.0, 1.0) == PointT<float>(1.0, 1.0) / 1.0);
  CHECK(PointT<long double>(1.0, 1.0) == PointT<long double>(1.0, 1.0) / 1.0);
  CHECK(p == PointT<double>(2.1, 3.1));
  CHECK(PointT<int>(0, 0) == PointT<int>(1, 1) / 2);
  CHECK(PointT<double>(0.5, 0.5) == PointT<int>(1, 1) / 2.0);
  DUMP(PointT<bool>(false, false));
  CHECK(PointT<long double>(0.0, 1.0) == PointT<long double>(1.0, 0.0).rotated(M_PI / 2));
  CHECK(PointT<double>(0.4, 0.4) == lerp(PointT<int>(0, 0), PointT<int>(1, 1), 0.4));
  DUMP(triangulate(Polygon{Point(0, 0), Point(10, 0), Point(10, 10), Point(0, 10)}));
}

