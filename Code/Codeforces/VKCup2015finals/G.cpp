#include <bits/stdc++.h>
typedef long long LL;

const int N = 100000 + 5;

struct Point {
    int x,y;

    void read() {
        scanf("%d%d",&x,&y);
    }

    bool operator < (const Point &rhs) const {
        if (x != rhs.x) return x < rhs.x;
        return y < rhs.y;
    }

    Point operator - (const Point &rhs) const {
        return Point{x - rhs.x,y - rhs.y};
    }

    LL operator * (const Point &rhs) const {
        return x * 1ll * rhs.y - y * 1ll * rhs.x;
    }
};

Point max[N],min[N];
int n,m;

bool work() {
    std::sort(min,min + m);
    int p = 0;
    for (int i = 1; i < m; ++ i) {
        if (min[i].y >= min[p].y) {
            p = i;
        }
    }
    for (int i = p; i < m; ++ i) {
        min[i - p] = min[i];
    }
    m -= p;
    if (m >= 2) {
        int top = 2;
        for (int i = 2; i < m; ++ i) {
            while (top >= 2 && (min[i] - min[top - 2]) * (min[top - 1]
                        - min[top - 2]) <= 0) -- top;
            min[top++] = min[i];
        }
        m = top;
    }
    std::sort(max,max + n);
    p = 0;
    for (int i = 0; i < m; ++ i) {
        Point o = {0,min[0].y};
        if (i) {
            o = min[i - 1];
        }
        while (p < n && max[p].x < min[i].x) {
            if ((min[i] - o) * (max[p] - o) >= 0) {
                return true;
            }
            p ++;
        }
    }
    return p != n;
}

int main() {
    scanf("%d%d",&n,&m);
    scanf("%*d%*d");
    for (int i = 0; i < n; ++ i) {
        max[i].read();
    }
    for (int i = 0; i < m; ++ i) {
        min[i].read();
    }
    puts(work() ? "Max" : "Min");
}
