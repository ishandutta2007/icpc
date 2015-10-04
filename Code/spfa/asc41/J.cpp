#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <vector>

using namespace std;
const int N = 33;
const double EPS = 1e-8;

int sign(double x) {return x < -EPS ? -1 : x > EPS;}

struct Point {
    double x, y;
    Point() {}
    Point(const double &x, const double &y): x(x), y(y) {}
    
    double norm() const {
        return sqrt(x*x + y*y);
    }
};

Point operator + (const Point &a, const Point &b) {
    return Point(a.x+b.x, a.y+b.y);
}
Point operator - (const Point &a, const Point &b) {
    return Point(a.x-b.x, a.y-b.y);
}
Point operator * (const double &b, const Point &a) {
    return Point(a.x*b, a.y*b);
}
double operator * (const Point &a, const Point &b) {
    return a.x*b.y - a.y*b.x;
}

struct Line {
    Point s, d;
    Line() {}
    Line(const Point &a, const Point &b):s(a) {
        d = b - a;
    }
};

Point intersection(const Line &a, const Line &b) {
    double lambda(((b.s - a.s) * b.d) / (a.d * b.d));
    return a.s + lambda * a.d;
}

char mp[N][N];
int look[N][N][N][N];
int n, m;

int isok(int x, int y) {
    if (x >= n || y >= m) return true;
    if (x < 0 || y < 0) return true;
    return mp[x][y] == '.';
}

int OK(const Line &a, const Line &b) {
    if (sign(a.d * b.d) == 0) {
        return true;
    }
    Point e = intersection(a, b);
    return isok(int(e.x-EPS), int(e.y-EPS)) &&
        isok(int(e.x-EPS), int(e.y+EPS)) &&
        isok(int(e.x+EPS), int(e.y-EPS)) &&
        isok(int(e.x+EPS), int(e.y+EPS));
}

int check(int x, int y, int X, int Y) {
    Line line1(Point(x+0.5, y+0.5), Point(X+0.5, Y+0.5));
    int s = min(x, X);
    int e = max(x, X);
    for (int i = s+1; i <= e; i++) {
        Line line2(Point(i, 100), Point(i, -100));
        if (!OK(line1, line2)) return false;
    }
    s = min(y, Y);
    e = max(y, Y);
    for (int i = s+1; i <= e; i++) {
        Line line2(Point(100, i), Point(-100, i));
        if (!OK(line1, line2)) return false;
    }
    return true;
}

void work() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++) {
        scanf("%s", mp[i]);
    }
    memset(look, 0, sizeof(look));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (mp[i][j] == '#') {
                continue;

            }
            for (int k = 0; k < n; k++) {
                for (int z = 0; z < m; z++) {
                    look[i][j][k][z] = check(i, j, k, z);
                }
            }
        }
    }
    /*
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            for (int k = 0; k < n; k++) {
                for (int z = 0; z < m; z++) {
                    printf("%d %d %d %d   %d\n", i, j, k, z, look[i][j][k][z]);
                }
            }
        }
    }
    */
    vector<pair<int, int> > ans;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int ok = 1;
            for (int k = 0; k < n && ok; k++) {
                for (int z = 0; z < m && ok; z++) {
                    if (i == k && j == z) continue;
                    int x = i, y = j, find = 0;
                    for (int x = i; x < n && mp[x][j] == '.'; x++) {
                        if (!look[x][j][k][z]) {
                            find = 1; break;
                        }
                    }
                    for (int x = i; x >= 0 && mp[x][j] == '.'; x--) {
                        if (!look[x][j][k][z]) {
                            find = 1; break;
                        }
                    }
                    for (int y = j; y < m && mp[i][y] == '.'; y++) {
                        if (!look[i][y][k][z]) {
                            find = 1; break;
                        }
                    }
                    for (int y = j; y >= 0 && mp[i][y] == '.'; y--) {
                        if (!look[i][y][k][z]) {
                            find = 1; break;
                        }
                    }
                    if (!find) {
                        ok = 0;
                    }
                }
            }
            if (ok) {
                ans.push_back(make_pair(i+1, j+1));
            }
        }
    }
    printf("%d\n", ans.size());
    for (int i = 0; i < ans.size(); i++) printf("%d %d\n", ans[i].first, ans[i].second);
}


int main() {
    freopen("jealous.in", "r", stdin);
    freopen("jealous.out", "w", stdout);
    work();
    return 0;
}
