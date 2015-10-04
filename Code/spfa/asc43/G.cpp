#include <bits/stdc++.h>

int n;
struct Graph {
    int x[2],y[2];
    std::vector<std::pair<int,int>> points;
}g[100 + 5];

Graph parallel(const Graph &a,const Graph &b) {
    Graph ret;
    ret.x[0] = a.x[0];
    ret.y[0] = a.y[0] - 1 - (b.y[1] - b.y[0]);
    ret.x[1] = a.x[1] + 1 + (b.x[1] - b.x[0]);
    ret.y[1] = a.y[1];
    ret.points.push_back({ret.x[0],ret.y[0]});
    for (auto t : a.points) {
        ret.points.push_back(t);
    }
    int dx = a.x[1] + 1 - b.x[0];
    int dy = a.y[0] - 1 - (b.y[1] - b.y[0]) - b.y[0];
    for (auto t : b.points) {
        ret.points.push_back({t.first + dx,t.second + dy});
    }
    ret.points.push_back({ret.x[1],ret.y[1]});
    return ret;
}

Graph series(const Graph &a,const Graph &b) {
    Graph ret;
    ret.x[0] = a.x[0];
    ret.y[0] = a.y[0];
    ret.x[1] = a.x[1] + (b.x[1] - b.x[0]);
    ret.y[1] = a.y[1] + 1 + (b.y[1] - b.y[0]);
    for (auto t : a.points) {
        ret.points.push_back(t);
    }
    int dx = ret.x[1] - b.x[1];
    int dy = ret.y[1] - b.y[1];
    for (auto t : b.points) {
        ret.points.push_back({t.first + dx,t.second + dy});
    }
    return ret;
}

int main() {
    freopen("grid.in","r",stdin);
    freopen("grid.out","w",stdout);
    while (scanf("%d",&n) == 1) {
        if (n == -1) break;
        g[0].x[0] = g[0].x[1] = g[0].y[0] = g[0].y[1] = 0;
        g[0].points.clear();
        g[0].points.push_back({0,0});

        for (int i = 1; i <= n; ++ i) {
            int a,b;
            char op[2];
            scanf("%s%d%d",op,&a,&b);
            if (op[0] == '|') {
                g[i] = parallel(g[a],g[b]);
            } else {
                g[i] = series(g[a],g[b]);
            }
            for (auto t : g[i].points) {
                assert(std::abs(t.first) <= (int)1e9);
                assert(std::abs(t.second) <= (int)1e9);
            }
        }
        printf("%d\n",g[n].points.size() + 2);
        printf("%d %d\n",g[n].x[0],g[n].y[0] - 1);
        for (auto t : g[n].points) {
            printf("%d %d\n",t.first,t.second);
        }
        printf("%d %d\n",g[n].x[1],g[n].y[1] + 1);
    }
}
