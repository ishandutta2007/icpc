#include <bits/stdc++.h>

const int INF = 0x3f3f3f3f;
int n,A[300][300];
int dis[2][300];

void dijkstra(int line,int dis[300]) {
    memset(dis,INF,sizeof(dis));
    std::priority_queue<std::pair<int,int>,std::vector<std::pair<int,int>>,
        std::greater<std::pair<int,int>>> que;
    for (int i = 1; i + 1 < n; ++ i) {
        dis[i] = A[line][i];
        que.push({dis[i],i});
    }
    while (!que.empty()) {
        int u = que.top().second;
        int tmp = que.top().first;
        que.pop();
        if (tmp != dis[u]) continue;
        for (int j = 1; j + 1 < n; ++ j) {
            if (j == u) continue;
            if (dis[j] > dis[u] + A[u][j]) {
                dis[j] = dis[u] + A[u][j];
                que.push({dis[j],j});
            }
        }
    }
}

int work() {
    int ret = A[0][n - 1];
    dijkstra(0,dis[0]);
    dijkstra(n - 1,dis[1]);
    int a = INF,b = INF;
    for (int i = 1; i + 1 < n; ++ i) {
        ret = std::min(ret,dis[0][i] + A[i][n - 1]);
        a = std::min(a,dis[0][i] + A[i][0]);
        b = std::min(b,dis[1][i] + A[i][n - 1]);
    }
    ret = std::min(ret,a + b);
    return ret;
}

int main() {
    while (scanf("%d",&n) == 1) {
        for (int i = 0; i < n; ++ i) {
            for (int j = 0; j < n; ++ j) {
                scanf("%d",&A[i][j]);
            }
        }
        printf("%d\n",work());
    }
}
