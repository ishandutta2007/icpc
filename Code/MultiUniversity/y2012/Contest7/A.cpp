#include <bits/stdc++.h>
typedef long long LL;

const LL Inf = 1e16;
const int N = 1314 + 5;
LL dis[N][4];
int love[N][4];
int n,m;

struct Edge {
    int v,w,c;
};
std::vector<Edge> edges[N];

void work() {
    std::priority_queue<std::pair<LL,int>,std::vector<std::pair<LL,int>>,
        std::greater<std::pair<LL,int>>> que;
    for (int i = 0; i <= n; ++ i)
        for (int j = 0; j < 4; ++ j)
            dis[i][j] = Inf;
    dis[n][0] = 0;
    edges[n] = edges[0];
    que.push({0ll,n << 2 | 0});
    while (!que.empty()) { 
        LL a = que.top().first;
        int u = que.top().second;
        int c = u & 3;
        u >>= 2;
        que.pop();
        if (dis[u][c] != a) continue;
        for (auto e : edges[u]) {
            if (e.c != c) continue;
            int cc = (c + 1) % 4;
            if (dis[e.v][cc] > dis[u][c] + e.w) {
                dis[e.v][cc] = dis[u][c] + e.w;
                que.push({dis[e.v][cc],e.v << 2 | cc});
            }
        }
    }
    for (int i = 0; i <= n; ++ i) {
        for (int j = 0; j < 4; ++ j) {
            if (dis[i][j] != Inf)
                que.push({dis[i][j],i << 2 | j});
            love[i][j] = 0;
        }
    }
    while (!que.empty()) {
        int u = que.top().second >> 2;
        int c = que.top().second & 3;
        que.pop();
        for (auto e : edges[u]) {
            if (e.c != c) continue;
            int cc = (c + 1) % 4;
            if (dis[e.v][cc] == dis[u][c] + e.w) {
                love[e.v][cc] = std::max(love[u][c] + 1,love[e.v][cc]);
            }
        }
    }
    if (dis[n - 1][0] == Inf) {
        puts("Binbin you disappoint Sangsang again, damn it!");
    } else {
        printf("Cute Sangsang, Binbin will come with a donkey after travelling %I64d meters and finding %d LOVE strings at last.\n",dis[n - 1][0],love[n - 1][0] / 4);
    }
}

int main() {
    int cas,ca = 0;
    scanf("%d",&cas);
    while (cas--) {
        scanf("%d%d",&n,&m);
        for (int i = 0; i < n; ++ i) {
            edges[i].clear();
        }
        for (int i = 0; i < m; ++ i) {
            int a,b,c,d;
            char s[2];
            scanf("%d%d%d%s",&a,&b,&c,s);
            a --; b --;
            d = s[0] == 'L' ? 0 : s[0] == 'O' ? 1 : s[0] == 'V' ? 2 : 3;
            edges[a].push_back({b,c,d});
            edges[b].push_back({a,c,d});
        }
        printf("Case %d: ",++ca);
        work();
    }
}
