#include <bits/stdc++.h>

const double eps = 1e-8;

inline int dcmp(double x) {
    return x < -eps ? -1 : x > eps;
}

struct Point;
using Vector = Point;
using Poly = std::vector<Point>;

struct Point {
    double x,y;

    Point() {}

    Point(double _x,double _y) : x(_x),y(_y) {}

    Point operator + (const Point &rhs) const {
        return Point(x + rhs.x,y + rhs.y);
    }

    Point operator - (const Point &rhs) const {
        return Point(x - rhs.x,y - rhs.y);
    }

    Point operator * (double t) const {
        return Point(x * t,y * t);
    }

    bool operator == (const Point &rhs) const {
        return dcmp(x - rhs.x) == 0 && dcmp(y - rhs.y) == 0;
    }

    double length() const {
        return hypot(x,y);
    }

    void read() {
        scanf("%lf%lf",&x,&y);
    }

    // *this 绕 o 逆时针旋转 angle 角度
    Point rotate(const Point &o,double angle) const {
        Point t = (*this) - o;
        double c = cos(angle),s = sin(angle);
        return Point(o.x + t.x * c - t.y * s,o.y + t.x * s + t.y * c);
    }

    // *this 向量的单位法向量(左转90度，长度归一化)
    Vector normal() const {
        double L = length();
        return Vector(-y / L,x / L);
    }

};

double det(const Point &a,const Point &b) {
    return a.x * b.y - a.y * b.x;
}

double dot(const Point &a,const Point &b) {
    return a.x * b.x + a.y * b.y;
}

// 用于极角排序的cmp函数
bool polar_cmp(const Point &a,const Point &b) {
    if (dcmp(a.y) * dcmp(b.y) <= 0) {
        if (dcmp(a.y) > 0 || dcmp(b.y) > 0) return dcmp(a.y - b.y) < 0;
        if (dcmp(a.y) == 0 && dcmp(b.y) == 0) return dcmp(a.x - b.x) < 0;
    }
    return dcmp(det(a,b)) > 0;
}

// 直线与直线的交点
Point intersection_line_line(Point p,Vector v,Point q,Vector w) {
    Vector u = p - q;
    double t = det(w,u) / det(v,w);
    return p + v * t;
}

// 点到直线距离
double distance_point_line(Point p,Point a,Point b) {
    Vector v1 = b - a,v2 = p - a;
    return std::abs(det(v1,v2)) / v1.length();
}

// 点到线段距离
double distance_point_segment(Point p,Point a,Point b) {
    if (a == b) return (p - a).length();
    Vector v1 = b - a,v2 = p - a,v3 = p - b;
    if (dcmp(dot(v1,v2)) < 0) return v2.length();
    else if (dcmp(dot(v1,v3)) > 0) return v3.length();
    else return std::abs(det(v1,v2)) / v1.length();
}

// 点在直线上的投影
Point projection_point_line(Point p,Point a,Point b) {
    Vector v = b - a;
    return a + v * (dot(v,p - a) / dot(v,v));
}

// 线段规范相交判定
bool intersection_segment_segment(Point a1,Point a2,Point b1,Point b2) {
    double c1 = det(a2 - a1,b1 - a1),c2 = det(a2 - a1,b2 - a1),
           c3 = det(b2 - b1,a1 - b1),c4 = det(b2 - b1,a2 - b1);
    return dcmp(c1) * dcmp(c2) < 0 && dcmp(c3) * dcmp(c4) < 0;
}

// 点在线段上判定
bool on_point_segment(Point p,Point a1,Point a2) {
    return dcmp(det(a1 - p,a2 - p)) == 0 && dcmp(dot(a1 - p,a2 -p)) < 0;
}

int main() {
}
