#include <bits/stdc++.h>

const int INF = 0x3f3f3f3f;
int A[100 + 5][10000 + 5];
int dp[100 + 5][10000 + 5];
int n,m,x,T;
std::pair<int,int> que[10000 + 5];

int work() {
    for (int i = 0; i <= n + 1; ++ i) {
        for (int j = 1; j <= m; ++ j) {
            dp[i][j] = -INF;
        }
    }
    for (int i = 0; i <= m; ++ i) {
        A[n + 1][i] = 0;
    }
    dp[0][x] = 0;
    for (int i = 1; i <= n + 1; ++ i) {
        int s = 0;
        int qf = 0,qe = 0;
        for (int j = 1; j <= m; ++ j) {
            if (dp[i - 1][j] != -INF) {
                int val = dp[i - 1][j] - s;
                while (qf != qe && que[qe - 1].first <= val) -- qe;
                que[qe++] = {val,j};
            }
            while (qf != qe && j - que[qf].second > T) ++ qf;
            s += A[i][j];
            if (qf != qe) {
                dp[i][j] = std::max(dp[i][j],que[qf].first + s);
            }
        }
        s = 0;
        qf = qe = 0;
        for (int j = m; j >= 1; -- j) {
            if (dp[i - 1][j] != -INF) {
                int val = dp[i - 1][j] - s;
                while (qf != qe && que[qe - 1].first <= val) -- qe;
                que[qe++] = {val,j};
            }
            while (qf != qe && que[qf].second - j > T) ++ qf;
            s += A[i][j];
            if (qf != qe) {
                dp[i][j] = std::max(dp[i][j],que[qf].first + s);
            }
        }
    }
    int ret = -INF;
    for (int i = 1; i <= m; ++ i)
        ret = std::max(ret,dp[n + 1][i]);
    return ret;
}

int main() {
    while (scanf("%d%d%d%d",&n,&m,&x,&T) == 4) {
        for (int i = 1; i <= n; ++ i) {
            for (int j = 1; j <= m; ++ j) {
                scanf("%d",&A[i][j]);
            }
        }
        printf("%d\n",work());
    }
}

