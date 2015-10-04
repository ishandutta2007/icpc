#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <vector>

const int N = 1000 + 5;
int n;
std::vector<int> edges[N];
int dis[N];

void dfs(int u,int fa,int d) {
    dis[d] ++;
    for (int i = 0; i < edges[u].size(); ++ i) {
        int v = edges[u][i];
        if (v == fa) continue;
        dfs(v,u,d + 1);
    }
}

int main() {
    while (scanf("%d",&n) == 1) {
        for (int i = 0; i < n; ++ i) {
            edges[i].clear();
        }
        for (int i = 0; i < n - 1; ++ i) {
            int a,b;
            scanf("%d%d",&a,&b); a --; b --;
            edges[a].push_back(b);
            edges[b].push_back(a);
        }
        memset(dis,0,sizeof(dis));
        dfs(0,-1,0);
        bool flag = false;
        for (int i = 0; i < n; ++ i) {
            if (dis[i] >= 2 && dis[i + 1] >= 1) {
                flag = true;
                break;
            }
        }
        puts(!flag ? "YES" : "NO");
    }
}

