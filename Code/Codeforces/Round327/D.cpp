#include <bits/stdc++.h>

const int INF = 0x3f3f3f3f;
int n,K,s;
int A[150];
int dp[2][75 + 1][(150 - 1) * 150 / 2 + 1];
int pd[2][75 + 1][(150 - 1) * 150 / 2 + 1];

inline void update(int &a,int b) {
    if (a > b) a = b;
}

int work() {
    int cnt = std::min(K,n - K);
    s = std::min(s,(n - 1) * n / 2);
    memset(dp,INF,sizeof(dp));
    memset(pd,INF,sizeof(pd));
    dp[0][0][0] = 0;
    int cur = 0,nex = 1;
    for (int i = K - 1; i >= 0; -- i) {
        for (int j = 0; j <= cnt; ++ j) {
            for (int k = 0; k <= s; ++ k) {
                if (dp[cur][j][k] == INF) continue;
                update(dp[nex][j][k],dp[cur][j][k] + A[i]);
                if (k + K - 1 - j - i <= s) {
                    update(dp[nex][j + 1][k + (K - 1 - j - i)],dp[cur][j][k]);
                }
                dp[cur][j][k] = INF;
            }
        }
        std::swap(cur,nex);
    }

    pd[0][0][0] = 0;
    int cc = 0,nn = 1;
    for (int i = K; i < n; ++ i) {
        for (int j = 0; j <= cnt; ++ j) {
            for (int k = 0; k <= s; ++ k) {
                if (pd[cc][j][k] == INF) continue;
                update(pd[nn][j][k],pd[cc][j][k]);
                if (k + i - (K + j) <= s) {
                    update(pd[nn][j + 1][k + (i - (K + j))],pd[cc][j][k] + A[i]);
                }
                pd[cc][j][k] = INF;
            }
        }
        std::swap(cc,nn);
    }
    int ret = INF;
    for (int i = 0; i <= cnt; ++ i) {
        for (int j = 1; j <= s; ++ j) {
            update(pd[cc][i][j],pd[cc][i][j - 1]);
        }
        for (int j = 0; j <= s - i * i; ++ j) {
            update(ret,dp[cur][i][j] + pd[cc][i][s - i * i - j]);
        }
    }
    return ret;
}

int main() {
    scanf("%d%d%d",&n,&K,&s);
    for (int i = 0; i < n; ++ i) {
        scanf("%d",A + i);
    }
    printf("%d\n",work());
}
