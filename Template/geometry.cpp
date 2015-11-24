#include <bits/stdc++.h>

const double eps = 1e-8;

inline int dcmp(double x) {
    return x < -eps ? -1 : x > eps;
}

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

    double len() const {
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
};

double det(const Point &a,const Point &b) {
    return a.x * b.y - a.y * b.x;
}

double dot(const Point &a,const Point &b) {
    return a.x * b.x + a.y * b.y;
}

bool polar_cmp(const Point &a,const Point &b) {
    if (dcmp(a.y) * dcmp(b.y) <= 0) {
        if (dcmp(a.y) > 0 || dcmp(b.y) > 0) return dcmp(a.y - b.y) < 0;
        if (dcmp(a.y) == 0 && dcmp(b.y) == 0) return dcmp(a.x - b.x) < 0;
    }
    return dcmp(det(a,b)) > 0;
}

int main() {
}
