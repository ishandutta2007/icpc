#include <bits/stdc++.h>

const int INF = 0x3f3f3f3f;
int dp[20][20][4][2];
int n;
int dir[4][2] = {1,0,0,1,-1,0,0,-1};
int graph[20][20];

int work() {
    if (graph[0][0] == 1) return -1;
    if (graph[0][0] == 2) return 980;
    std::queue<int> que;
    memset(dp,-1,sizeof(dp));
    dp[0][0][0][0] = 0;
    que.push(0);
    que.push(0);
    que.push(0);
    que.push(0);
    while (!que.empty()) {
        int x = que.front(); que.pop();
        int y = que.front(); que.pop();
        int d = que.front(); que.pop();
        int h = que.front(); que.pop();

        if (h == 0 && graph[x][y] == 2 && dp[x][y][d][1] == -1) {
            dp[x][y][d][1] = dp[x][y][d][h] + 1;
            que.push(x);
            que.push(y);
            que.push(d);
            que.push(1);
        }

        {
            int tx = x + dir[d][0];
            int ty = y + dir[d][1];
            if (tx >= 0 && tx < n && ty >= 0 && ty < n
                    && graph[tx][ty] != 1
                    && dp[tx][ty][d][h] == -1) {
                dp[tx][ty][d][h] = dp[x][y][d][h] + 1;
                que.push(tx);
                que.push(ty);
                que.push(d);
                que.push(h);
            }
        }

        for (int dd = -1; dd <= 1; dd += 2) {
            int ddd = (d + dd + 4) % 4;
            int tx = x;
            int ty = y;
            if (tx >= 0 && tx < n && ty >= 0 && ty < n
                    && graph[tx][ty] != 1
                    && dp[tx][ty][ddd][h] == -1) {
                dp[tx][ty][ddd][h] = dp[x][y][d][h] + 1;
                que.push(tx);
                que.push(ty);
                que.push(ddd);
                que.push(h);
            }
        }
    }
    int tmp = INF;
    for (int d = 0; d < 4; ++ d) {
        if (dp[0][0][d][1] != -1) {
            tmp = std::min(tmp,dp[0][0][d][1]);
        }
    }
    if (tmp == INF) return -1;
    return 1000 - tmp * 10 - 10;
}

int main() {
    int cas;
    scanf("%d",&cas);
    while (cas--) {
        scanf("%d",&n);
        memset(graph,0,sizeof(graph));
        int a,b,c;
        while (scanf("%d%d%d",&a,&b,&c) == 3) {
            if (a == -1) break;
            if (a == 1 || a == 2) {
                graph[b][c] = 1;
            } else {
                graph[b][c] = 2;
            }
        }
        printf("%d\n",work());
    }
}
