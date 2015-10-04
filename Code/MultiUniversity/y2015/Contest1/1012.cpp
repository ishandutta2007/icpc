#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <set>
#include <vector>
#include <time.h>
#include <stdlib.h>
#include <math.h>

const int N = 20000 + 5;
struct Circle {
    double x,y,r;

    void read() {
        scanf("%lf%lf%lf",&x,&y,&r);
    }

    void rotate(double angle) {
        double tx = x * cos(angle) - y * sin(angle);
        double ty = x * sin(angle) + y * cos(angle);
        x = tx;
        y = ty;
    }

    bool operator < (const Circle &rhs) const {
        return r < rhs.r;
    }
} circle[N];
int n;

const double pi = atan(1.0) * 4;
const double eps = 1e-8;

int dcmp(double x) {
    return x < -eps ? -1 : x > eps;
}

double sqr(double x) {
    return x * x;
}

bool contains(const Circle &a,const Circle &b) {
    return sqrt(sqr(a.x - b.x) + sqr(a.y - b.y)) < a.r;
}

int sg[N];

bool work() {
    double angle = rand() * 1. / 32768 * 2 * pi;
    for (int i = 0; i < n; ++ i) {
        circle[i].rotate(angle);
    }
    std::sort(circle,circle + n);
    std::set<std::pair<double,int> > set;
    std::set<std::pair<double,int> >::iterator it,it2;
    for (int i = 0; i < n; ++ i) {
        sg[i] = 0;
        Circle &c = circle[i];
        it = set.lower_bound(std::make_pair(c.x - c.r,-1));
        it2 = set.lower_bound(std::make_pair(c.x + c.r,-1));
        if (it2 != set.end()) it2 ++;
        while (it != it2) {
            int id = it->second;
            if (contains(c,circle[id])) {
                sg[i] ^= sg[id] + 1;
                set.erase(it++);
            } else {
                ++ it;
            }
        }
        set.insert(std::make_pair(c.x,i));
    }
    int ret = 0;
    for (it = set.begin(); it != set.end(); ++ it) {
        ret ^= sg[it->second] + 1;
    }
    return ret;
}

int main() {
    srand(time(NULL));
    int cas;
    scanf("%d",&cas);
    while (cas--) {
        scanf("%d",&n);
        for (int i = 0; i < n; ++ i) {
            circle[i].read();
        }
        puts(work() ? "Alice" : "Bob");
    }
}
