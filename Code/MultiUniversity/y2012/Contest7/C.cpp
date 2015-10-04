#include <bits/stdc++.h>

const int INF = 0x3f3f3f3f;
int n,m,x;
int dp[2][1000];
std::pair<int,int> A[50][1000];

inline void update(int &a,int b) {
    if (a > b) a = b;
}

int work() {
    memset(dp,INF,sizeof(dp));
    for (int i = 0; i < m; ++ i) 
        std::sort(A[i],A[i] + n);
    for (int i = 0; i < n; ++ i) {
        dp[0][i] = std::abs(x - A[0][i].first) + A[0][i].second;
    }
    for (int i = 0; i + 1 < m; ++ i) {
        int cur = i & 1;
        int nex = cur ^ 1;
        for (int j = 0; j < n; ++ j) 
            dp[nex][j] = INF;
        int t = INF;
        for (int j = 0,k = 0; j < n; ++ j) {
            while (k < n && A[i][k].first <= A[i + 1][j].first) {
                t = std::min(t,dp[cur][k] - A[i][k].first);
                ++ k;
            }
            update(dp[nex][j],t + A[i + 1][j].first + A[i + 1][j].second);
        }
        t = INF;
        for (int j = n - 1,k = n - 1; j >= 0; -- j) {
            while (k >= 0 && A[i][k].first >= A[i + 1][j].first) {
                update(t,dp[cur][k] + A[i][k].first);
                -- k;
            }
            update(dp[nex][j],t - A[i + 1][j].first + A[i + 1][j].second);
        }
    }
    int ret = INF;
    for (int i = 0; i < n; ++ i)
        update(ret,dp[m - 1 & 1][i]);
    return ret;
}

int main() {
    int cas;
    scanf("%d",&cas);
    while (cas--) {
        scanf("%d%d%d",&m,&n,&x);
        for (int i = 0; i < m; ++ i)
            for (int j = 0; j < n; ++ j)
                scanf("%d",&A[i][j].first);
        for (int i = 0; i < m; ++ i)
            for (int j = 0; j < n; ++ j)
                scanf("%d",&A[i][j].second);
        printf("%d\n",work());
    }
}
