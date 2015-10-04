#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

typedef __int64 lld;

struct Point {
    lld x, y;
    Point() {}
    Point(const lld &x, const lld &y): x(x), y(y) {}
    
    void in() {
        scanf("%I64d%I64d", &x, &y);
    }
};

Point operator + (const Point &a, const Point &b) {
    return Point(a.x + b.x, a.y + b.y);
}
Point operator - (const Point &a, const Point &b) {
    return Point(a.x - b.x, a.y - b.y);
}
lld operator * (const Point &a, const Point &b) {
    return a.x * b.y - a.y * b.x;
}

const int N = 1e5 + 5;

Point points[N], A, B;
Point left, right;
int n;

void work() {
    for (int i = 0; i < n; i++) {
        points[i].in();
    }
    A.in(); B.in();

    lld ans = 0;
    for (int i = 0; i < n; i++) {
        if ((A - points[i]) * (B - points[i]) == 0) continue;
        if ((A - points[i]) * (B - points[i]) > 0) {
            right = A; left = B;
        }else {
            right = B; left = A;
        }
        int L, R;
        int l = 1, r = n - 1;
        while (r >= l) {
            int mid = (r + l) >> 1;
            Point &e = points[(mid+i)%n];
            if ((right - points[i]) * (e - points[i]) > 0) {
                r = mid - 1;
            }else {
                l = mid + 1;
            }
        }
        L = r + 1;

        l = 1, r = n - 1;
        while (r >= l) {
            int mid = (r + l) >> 1;
            Point &e = points[(mid+i)%n];
            if ((e - points[i]) * (left - points[i]) > 0) {
                l = mid + 1;
            }else {
                r = mid - 1;
            }
        }
        R = l - 1;

        if (L >= 1 && L < n && R >= 1 && R < n && R >= L) {
            ans += R - L + 1;
        }
    }
    printf("%I64d\n", ans >> 1);
}

int main() {
    freopen("kingdom.in", "r", stdin);
    freopen("kingdom.out", "w", stdout);
    while (scanf("%d", &n) == 1 && n) {
        work();
    }
    return 0;
}
