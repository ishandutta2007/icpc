const double eps = 1e-8;

inline int dcmp(double x) {
    return x > eps ? 1 : x < -eps ? -1 : 0;
}

struct Point {
    double x,y;

    Point(double _x = 0,double _y = 0):
        x(_x),y(_y) {}

    bool operator == (const Point &rhs) const {
        return dcmp(x - rhs.x) == 0 && dcmp(y - rhs.y) == 0;
    }

    Point operator + (const Point &rhs) const {
        return Point(x + rhs.x,y + rhs.y);
    }

    Point operator - (const Point &rhs) const {
        return Point (x - rhs.x,y - rhs.y);
    }

    double operator * (const Point &rhs) const {
        return x * rhs.y - y * rhs.x;
    }

    double operator % (const Point &rhs) const {
        return x * rhs.x + y * rhs.y;
    }

    double len() const {
        return hypot(x,y);
    }

    Point rotate(const Point &rhs,double angle) const {
        Point t = (*this) - rhs;
        double c = cos(angle),s = sin(angle);
        return Point(rhs.x + t.x * c - t.y * s,rhs.y + t.x * s + t.y * c);
    }

    void read() {
        scanf("%lf%lf",&x,&y);
    }
};

bool polar_cmp(const Point &lhs,const Point &rhs) {
    if (dcmp(lhs.y) * dcmp(rhs.y) <= 0) {
        if (dcmp(lhs.y) > 0 || dcmp(rhs.y) > 0) return dcmp(lhs.y - rhs.y) < 0;
        if (dcmp(lhs.y) == 0 && dcmp(rhs.y) == 0) return dcmp(lhs.x - rhs.x) < 0;
    }
    return dcmp(lhs * rhs) > 0;
}
