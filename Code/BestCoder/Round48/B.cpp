#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <vector>
#include <queue>
typedef long long LL;


const int N = 100000 + 5;
int n,m;
std::vector<int> edges[N];
bool vis[N];
int mark[N];

int bfs(int source) {
    std::queue<int> que;
    que.push(source);
    int c[2] = {};
    vis[source] = true;
    while (!que.empty()) {
        int u = que.front(); que.pop();
        c[mark[u]] ++;
        for (int i = 0; i < edges[u].size(); ++ i) {
            int v = edges[u][i];
            if (vis[v]) {
                if (mark[v] == mark[u]) {
                    return -1;
                }
            } else {
                vis[v] = true;
                mark[v] = mark[u] ^ 1;
                que.push(v);
            }
        }
    }
    return std::max(c[0],c[1]);
}

bool work() {
    std::fill(vis,vis + n,false);
    int a = 0,b = 0;
    for (int i = 0; i < n; ++ i) {
        if (!vis[i]) {
            int t = bfs(i);
            if (t == -1) return false;
            a += t;
        }
    }
    if (a == n) a --;
    b = n - a;
    if (a < 1 || b < 1) return false;
    printf("%d %d\n",a,b);
    return true;
}


int main() {
    int cas;
    scanf("%d",&cas);
    while (cas--) {
        scanf("%d%d",&n,&m);
        for (int i = 0; i < n; ++ i) {
            edges[i].clear();
        }
        for (int i = 0; i < m; ++ i) {
            int x,y;
            scanf("%d%d",&x,&y); x --; y --;
            edges[x].push_back(y);
            edges[y].push_back(x);
        }
        if (!work()) {
            puts("Poor wyh");
        }
    }
}
