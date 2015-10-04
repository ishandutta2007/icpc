#include <bits/stdc++.h>
typedef long long LL;

const LL Inf = (LL)1e16;
const int N = 300000 + 5;
int n,K;
int A[N];
LL dp[2][5000 + 1];
int cnt[N];

inline void update(LL &a,LL b) {
    if (a > b) a = b;
}

LL work() {
    std::sort(A,A + n);
    for (int i = 0; i < K; ++ i) {
        int c = 1;
        int t = i;
        while (t + K < n) t += K,c ++;
        cnt[c] ++;
    }
    int a = -1,b = -1,c = -1,d = -1;
    for (int i = 0; i < N; ++ i) {
        if (cnt[i] != 0) {
            if (a == -1) {
                a = i;
                b = cnt[i];
            } else {
                c = i;
                d = cnt[i];
            }
        }
    }
    if (c == -1) {
        c = d = 0;
    }
    std::fill(dp[0],dp[0] + d + 1,Inf);
    dp[0][0] = 0;
    for (int i = 0; i <= b; ++ i) {
        int cur = i & 1;
        int nex = cur ^ 1;
        std::fill(dp[nex],dp[nex] + d + 1,Inf);
        for (int j = 0; j <= d; ++ j) {
            if (dp[cur][j] == Inf) continue;
            int x = -1,y = -1;

            x = i * a + j * c;
            y = i * a + (j + 1) * c - 1;
            if (y < n) {
                update(dp[cur][j + 1],dp[cur][j] + A[y] - A[x]);
            }
            y = (i + 1) * a - 1 + j * c;
            if (y < n) {
                update(dp[nex][j],dp[cur][j] + A[y] - A[x]);
            }
        }
    }
    return dp[b & 1][d];
}

int main() {
    scanf("%d%d",&n,&K);
    for (int i = 0; i < n; ++ i) {
        scanf("%d",A + i);
    }
    printf("%I64d\n",work());
}
