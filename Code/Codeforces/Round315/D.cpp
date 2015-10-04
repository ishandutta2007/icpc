#include <bits/stdc++.h>

const double eps = 1e-5;

int dcmp(double x) {
    return x < -eps ? -1 : x > eps;
}

struct Line {
    int a,b,c,id;

    bool operator < (const Line &rhs) const {
        return a * 1ll * rhs.b < rhs.a * b;
    }

    void show() {
        printf("l : %d %d %d %d\n",a,b,c,id);
    }
};

const int N = 100000 + 5;
int n,K;
std::vector<Line> lines;

struct Point {
    double x,y;
    int a,b;

    void show() {
        printf("p : %f %f %d %d\n",x,y,a,b);
    }
};

bool intersection(const Line &lhs,const Line &rhs,Point &o) {
    if (lhs.a * 1ll * rhs.b == rhs.a * 1ll * lhs.b) {
        return false;
    }
    if (lhs.a != 0) {
        o.y = (rhs.a * 1. / lhs.a * lhs.c - rhs.c)
            / (rhs.b - rhs.a * 1. / lhs.a * lhs.b);
        o.x = - (lhs.b * 1. * o.y + lhs.c) / lhs.a;
    } else {
        o.y = (lhs.a * 1. / rhs.a * rhs.c - lhs.c)
            / (lhs.b - lhs.a * 1. / rhs.a * rhs.b);
        o.x = - (rhs.b * 1. * o.y + rhs.c) / rhs.a;
    }
    o.a = lhs.id;
    o.b = rhs.id;
    return true;
}

bool point_on_line(const Point &o,const Line &l) {
    return dcmp(l.a * 1. * o.x + l.b * 1. * o.y + l.c) == 0;
}

std::vector<Point> answer;

bool search(std::vector<Line> vl,int K) {
    if (vl.size() <= K) {
        puts("YES");
        printf("%d\n",answer.size() + vl.size());
        for (auto &o : answer) {
            printf("%d %d\n",o.a + 1,o.b + 1);
        }
        for (auto &l : vl) {
            printf("%d -1\n",l.id + 1);
        }
        return true;
    }
    if (K == 0) {
        return false;
    }
    for (int i = 0; i < K + 1; ++ i) {
        for (int j = 0; j < i; ++ j) {
            Point o;
            if (!intersection(vl[i],vl[j],o)) {
                continue;
            }
            std::vector<Line> nvl;
            for (auto &l : vl) {
                if (!point_on_line(o,l)) {
                    nvl.push_back(l);
                }
            }
            answer.push_back(o);
            if (search(nvl,K - 1)) {
                return true;
            }
            answer.pop_back();
        }
    }
    return false;
}

bool work() {
    while (K && lines.size() > K * K) {
        bool flag = false;
        for (int i = 0; i < K * K + 1; ++ i) {
            for (int j = 0; j < i; ++ j) {
                Point o;
                if (!intersection(lines[i],lines[j],o)) {
                    continue;
                }
                int cnt = 0;
                for (int k = 0; k < K * K + 1; ++ k) {
                    if (point_on_line(o,lines[k])) {
                        cnt ++;
                    }
                }
                if (cnt > K) {
                    flag = true;
                    answer.push_back(o);
                    int p = 0;
                    for (auto &l : lines) {
                        if (!point_on_line(o,l)) {
                            lines[p++] = l;
                        }
                    }
                    lines.resize(p);
                    K --;
                    break;
                }
            }
            if (flag) {
                break;
            }
        }
        if (!flag) {
            return false;
        }
    }
    return search(lines,K);
}

int main() {
    scanf("%d%d",&n,&K);
    for (int i = 0; i < n; ++ i) {
        int a,b,c;
        scanf("%d%d%d",&a,&b,&c);
        lines.push_back({a,b,c,i});
    }
    if (!work()) {
        puts("NO");
    }
}
