#include <bits/stdc++.h>

const int N = 15000 + 5;
const int MOD = (int)1e9 + 7;
int n,A[5];
int dp[N][1 << 5];
int F[N],Finv[N],Inv[N];

void init() {
    Inv[1] = 1;
    for (int i = 2; i < N; ++ i) {
        Inv[i] = Inv[MOD % i] * 1ll * (MOD - MOD / i) % MOD;
    }
    F[0] = Finv[0] = 1;
    for (int i = 1; i < N; ++ i) {
        F[i] = F[i - 1] * 1ll * i % MOD;
        Finv[i] = Finv[i - 1] * 1ll * Inv[i] % MOD;
    }
}

int comb(int a,int b) {
    if (b < 0 || b > a) return 0;
    return F[a] * 1ll * Finv[b] % MOD * Finv[a - b] % MOD;
}

inline void add(int &a,int b) {
    a += b;
    if (a >= MOD) a -= MOD;
    if (a < 0) a += MOD;
}

int solve() {
    for (int mask = 0; mask < 1 << 5; ++ mask) {
        dp[0][mask] = 1;
    }
    for (int i = 1; i <= n; ++ i) {
        for (int mask = 0; mask < 1 << 5; ++ mask) {
            dp[i][mask] = dp[i - 1][mask] * 1ll *  (5 - __builtin_popcount(mask)) % MOD;
            for (int j = 0; j < 5; ++ j) {
                if (i - 1 >= A[j] && (~mask >> j & 1)) {
                    add(dp[i][mask], - dp[i - 1 - A[j]][mask ^ 1 << j]
                            * 1ll * comb(i - 1,A[j]) % MOD);
                }
            }
        }
    }
    return dp[n][0];
}

int work() {
    int ret = solve();
    if (A[0] > 0) {
        n --;
        A[0] --;
        ret = (ret + MOD - solve()) % MOD;
    }
    return ret;
}

int main() {
    init();
    int cas,ca = 0;
    scanf("%d",&cas);
    while (cas--) {
        scanf("%d",&n);
        for (int i = 0; i < 5; ++ i)
            scanf("%d",A + i);
        printf("Case #%d: %d\n",++ca,work());
    }
}
