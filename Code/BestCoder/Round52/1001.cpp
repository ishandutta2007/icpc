#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <vector>
#include <string>
typedef long long LL;

const int INF = 0x3f3f3f3f;
int graph[16][16];
int n,m;
int dp[1 << 16][16];

int work() {
    memset(dp,INF,sizeof(dp));
    for (int i = 0; i < n; ++ i) {
        graph[i][i] = 0;
    }
    dp[1][0] = 0;
    for (int k = 0; k < n; ++ k) {
        for (int i = 0; i < n; ++ i) {
            for (int j = 0; j < n; ++ j) {
                graph[i][j] = std::min(graph[i][j],graph[i][k] + graph[k][j]);
            }
        }
    }
    for (int mask = 0; mask < 1 << n; ++ mask) {
        for (int i = 0; i < n; ++ i) {
            if (dp[mask][i] == INF) continue;
            for (int j = 0; j < n; ++ j) {
                if ((mask >> j & 1) == 0) {
                    dp[mask ^ 1 << j][j] = std::min(dp[mask ^ 1 << j][j],
                            dp[mask][i] + graph[i][j]);
                }
            }
        }
    }
    int ret = INF;
    for (int i = 0; i < n; ++ i) {
        ret = std::min(ret,dp[(1 << n) - 1][i] + graph[i][0]);
    }
    return ret;
}

int main() {
    int cas;
    scanf("%d",&cas);
    while (cas--) {
        scanf("%d%d",&n,&m);
        memset(graph,INF,sizeof(graph));
        for (int i = 0; i < m; ++ i) {
            int a,b,c;
            scanf("%d%d%d",&a,&b,&c); a --; b --;
            graph[a][b] = graph[b][a] = std::min(graph[a][b],c);
        }
        printf("%d\n",work());
    }
}
