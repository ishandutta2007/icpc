#include <bits/stdc++.h>
#ifdef LOCAL
#include "debuger.hpp"
#else
#define DUMP(...) 1145141919810
#define CHECK(...) (__VA_ARGS__)
#endif

const double eps = 1e-8;

template<typename T> inline int cmpT(T x) { return x < 0 ? -1 : x > 0; }
template<> inline int cmpT(double x) { return x < -eps ? -1 : x > eps; }

template<typename T>
struct VecT {
  T x = 0;
  T y = 0;

  static_assert(std::is_arithmetic<T>::value, "Should be an arithmetic type.");

  VecT() {}
  VecT(T x, T y) : x(x), y(y) {}
  VecT operator + (const VecT& rhs) const { return VecT(x + rhs.x, y + rhs.y); }
  VecT& operator += (const VecT& rhs) { *this = *this + rhs; return *this; }
  VecT operator - (const VecT& rhs) const { return VecT(x - rhs.x, y - rhs.y); }
  VecT& operator -= (const VecT& rhs) { *this = *this - rhs; return *this; }
  VecT operator * (T t) const { return VecT(x * t, y * t); }
  VecT& operator *= (T t) { *this = *this * t; return *this; }
  bool operator == (const VecT& rhs) const { return cmpT(x - rhs.x) == 0 && cmpT(y - rhs.y) == 0; }
  bool operator != (const VecT& rhs) const { return !(*this == rhs); }
  T length_sqr() const { return x * x + y * y; }
  VecT rotate90() const { return VecT(-y, x); }

  double length() const { return hypot(x, y); }
  VecT<double> rotate(double angle) const {
    double c = cos(angle), s = sin(angle);
    return VecT<double>(x * c - y * s, x * s + y * c);
  }
  VecT<double> operator / (double t) const { return VecT<double>(x / t, y / t); }
  VecT<double>& operator /= (double t) { *this = *this / t; return *this; }
  template<typename U> VecT<U> convert() const { return VecT<U>(x, y); }
};

template<typename T>
std::string to_string(const VecT<T>& v) {
  return std::string("VecT{x=") + std::to_string(v.x) + ",y=" + std::to_string(v.y) + "}";
}

template<typename T> T det(const VecT<T>& a, const VecT<T>& b) { return a.x * b.y - a.y * b.x; }
template<typename T> T dot(const VecT<T>& a, const VecT<T>& b) { return a.x * b.x + a.y * b.y; }

template<typename T> using PointT = VecT<T>;
template<typename T> using PolygonT = std::vector<PointT<T>>;

template<typename T>
bool polar_cmp(const VecT<T>& a,const VecT<T>& b) {
  if (cmpT(a.y) * cmpT(b.y) <= 0) {
    if (cmpT(a.y) > 0 || cmpT(b.y) > 0) return cmpT(a.y - b.y) < 0;
    if (cmpT(a.y) == 0 && cmpT(b.y) == 0) return cmpT(a.x - b.x) < 0;
  }
  return cmpT(det(a,b)) > 0;
}

template<typename T>
PointT<double> intersection_line_line(const PointT<T>& p, const PointT<T>& pp, const PointT<T>& q, const PointT<T>& qq) {
  const VecT<T> u = p - q, v = pp - p, w = qq - q;
  const double ratio = det(w, u) / static_cast<double>(det(v, w));
  return PointT<double>(p.x + v.x * ratio, p.y + v.y * ratio);
}

template<typename T>
PointT<double> projection_point_line(const PointT<T>& p, const PointT<T>& a, const PointT<T>& b) {
  const VecT<T> v = b - a;
  const double ratio = dot(v, p - a) / static_cast<double>(dot(v, v));
  return PointT<double>(a.x + v.x * ratio, a.y + v.y * ratio);
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
bool intersection_proper_segment_segment(
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
bool intersection_segment_segment(
    const PointT<T>& a1, const PointT<T>& a2, const PointT<T>& b1, const PointT<T>& b2) {
  if (intersection_proper_segment_segment(a1, a2, b1, b2)) return true;
  return
    on_point_segment(a1, b1, b2) || on_point_segment(a2, b1, b2) ||
    on_point_segment(b1, a1, a2) || on_point_segment(b2, a1, a2);
}

template<typename T>
bool in_point_polygon(const PointT<T>& o, const PolygonT<T> &poly, bool flag) {
  // flag == true means boundary counts as inner side.
  int t = 0;
  PointT<T> a, b;
  const int n = poly.size();
  for (int i = 0; i < n; ++ i) if (on_point_segment(o, poly[i], poly[(i + 1) % n])) return flag;
  for (int i = 0; i < n; ++ i) {
    a = poly[i];
    b = poly[(i + 1) % n];
    if (cmpT(a.y - b.y) > 0) std::swap(a,b);
    if (cmpT(det(a - o, b - o)) < 0 && cmpT(a.y - o.y) < 0 && cmpT(o.y - b.y) <= 0) ++t;
  }
  return t & 1;
}

using Point = PointT<double>;
using Vector = Point;
using Polygon = std::vector<Point>;

inline int dcmp(double x) { return cmpT(x); }

void geom_test() {
  DUMP(intersection_line_line(PointT<int>(1, 0), VecT<int>(0, 1), PointT<int>(0, 0), VecT<int>(1, 1)));
  DUMP(projection_point_line(PointT<int>(1, 1), PointT<int>(0, 0), PointT<int>(3, -2)));
  DUMP(distance_point_segment(PointT<int>(1, 1), PointT<int>(9, -7), PointT<int>(3, -2)));
  DUMP(distance_point_line(PointT<int>(1, 1), PointT<int>(9, -7), PointT<int>(3, -2)));
  DUMP(PointT<int>(1, 1).rotate90());
  DUMP(PointT<int>(1, 1).rotate(1.57));
  DUMP(PointT<int>(1, 1).rotate(M_PI / 2));
  DUMP(PointT<long long>(1, 10000).convert<double>());
  DUMP(PointT<double>(1.7, -1.7).convert<int>());
}

int main() {
  geom_test();
}
