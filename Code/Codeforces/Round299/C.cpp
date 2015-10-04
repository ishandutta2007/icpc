#include <bits/stdc++.h>

const int N = 200000 + 5;
int n,A[N],B[N];

struct Point {
    int x,y;

    bool operator < (const Point &rhs) const {
        // 1 / x < 1 / rhs.x
        if (x != rhs.x) return x > rhs.x;
        return y > rhs.y;
    }
};

Point pt[N];

bool cross(Point a,Point b,Point c) {
    return 1. / a.x / b.y - 1. / a.x / c.y - 1. / c.x / b.y
        - 1. / a.y / b.x + 1. / a.y / c.x + 1. / c.y / b.x > 0;
}

void work() {
    std::sort(pt,pt + n);
    int tot = 1;
    for (int i = 1; i < n; ++ i) {
        if (pt[i].y > pt[tot - 1].y)
            pt[tot++] = pt[i];
    }
    int top = 0;
    for (int i = 0; i < tot; ++ i) {
        while (top >= 2 && cross(pt[i],pt[top - 1],pt[top - 2])) -- top;
        pt[top++] = pt[i];
    }
    std::set<std::pair<int,int>> set;
    for (int i = 0; i < top; ++ i) {
        set.insert({pt[i].x,pt[i].y});
    }
    bool flag = true;
    for (int i = 0; i < n; ++ i) {
        if (set.find({A[i],B[i]}) != set.end()) {
            if (flag) flag = false;
            else putchar(' ');
            printf("%d",i + 1);
        }
    }
    puts("");
}

int main() {
    scanf("%d",&n);
    for (int i = 0; i < n; ++ i) {
        scanf("%d%d",A + i,B + i);
        pt[i] = {A[i],B[i]};
    }
    work();
}
