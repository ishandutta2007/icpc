#include <bits/stdc++.h>
typedef long long LL;

const int N = 18;
LL dp[1 << 18][18];
int A[N],graph[N][N];
int n,m,K;

inline void update(LL &a,LL b) {
    if (a < b) a = b;
}

LL work() {
    for (int i = 0; i < n; ++ i) {
        dp[1 << i][i] = A[i];
    }
    for (int mask = 0; mask < 1 << n; ++ mask) {
        for (int i = 0; i < n; ++ i) {
            if (mask >> i & 1) {
                for (int j = 0; j < n; ++ j) {
                    if (~mask >> j & 1) {
                        update(dp[mask ^ 1 << j][j],dp[mask][i] 
                                + graph[i][j] + A[j]);
                    }
                }
            }
        }
    }
    LL ret = 0;
    for (int mask = 0; mask < 1 << n; ++ mask) {
        if (__builtin_popcount(mask) != m) continue;
        for (int i = 0; i < n; ++ i) {
            update(ret,dp[mask][i]);
        }
    }
    return ret;
}

int main() {
    scanf("%d%d%d",&n,&m,&K);
    for (int i = 0; i < n; ++ i) {
        scanf("%d",A + i);
    }
    for (int i = 0; i < K; ++ i) {
        int a,b,c;
        scanf("%d%d%d",&a,&b,&c); a --; b --;
        graph[a][b] = c;
    }
    printf("%I64d\n",work());
}
