#include <bits/stdc++.h>
typedef long long LL;

typedef std::pair<short,short> Point;

const int N = 1000 + 5;
int idx[N * 3][N * 3];
std::list<Point> list[N * N];
int tot;
std::vector<Point> bad;
int n,m,o,l;
char str[N];
int dir[4][2] = {0,-1,0,1,-1,0,1,0};

inline int sqr(int x) {
    return x * x;
}

int dx,dy;

bool mark[N][N];

LL work() {
    for (int i = 0; i < n; ++ i) {
        for (int j = 0; j < m; ++ j) {
            mark[i][j] = false;
        }
    }
    for (int i = 0; i < o; ++ i) {
        mark[bad[i].first][bad[i].second] = true;
    }
    for (int i = 0; i < m; ++ i) {
        bad.push_back({-1,i});
        bad.push_back({n,i});
    }
    for (int i = 0; i < n; ++ i) {
        bad.push_back({i,-1});
        bad.push_back({i,m});
    }
    tot = 1;
    for (int i = 0; i < N * 3; ++ i) {
        for (int j = 0; j < N * 3; ++ j) {
            idx[i][j] = 0;
        }
    }
    for (int i = 0; i < n; ++ i) {
        for (int j = 0; j < m; ++ j) {
            if (!mark[i][j]) {
                list[tot].clear();
                list[tot].push_back({i + N,j + N});
                idx[i + N][j + N] = tot ++;
            }
        }
    }
    dx = dy = 0;
    for (auto &t : bad) {
        t.first += N;
        t.second += N;
    }
    for (int i = 0; i < l; ++ i) {
        int d;
        if (str[i] == 'L') d = 0;
        else if (str[i] == 'R') d = 1;
        else if (str[i] == 'U') d = 2;
        else d = 3;
        for (auto &t : bad) {
            int x = t.first - dir[d][0] - dx;
            int y = t.second - dir[d][1] - dy;
            int xx = x - dir[d][0];
            int yy = y - dir[d][1];
            if (idx[xx][yy] == 0) {
                idx[xx][yy] = idx[x][y];
            } else {
                list[idx[xx][yy]].splice(list[idx[xx][yy]].end(),list[idx[x][y]]);
            }
            idx[x][y] = 0;
        }
        dx += dir[d][0];
        dy += dir[d][1];
    }
    LL ret = 0;
    for (int i = 0; i < N * 3; ++ i) {
        for (int j = 0; j < N * 3; ++ j) {
            if (list[idx[i][j]].empty()) continue;
            int x = i + dx;
            int y = j + dy;
            for (auto &t : list[idx[i][j]]) {
                ret += sqr(t.first - x) + sqr(t.second - y);
            }
        }
    }
    return ret;
}

int main() {
    int cas,ca = 0;
    scanf("%d",&cas);
    while (cas--) {
        scanf("%d%d%d%d",&n,&m,&o,&l);
        bad.clear();
        for (int i = 0; i < o; ++ i) {
            int a,b;
            scanf("%d%d",&a,&b); a --; b --;
            bad.push_back({a,b});
        }
        scanf("%s",str);
        printf("Case #%d: %lld\n",++ca,work());
    }
}
