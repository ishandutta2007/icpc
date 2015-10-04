#include <bits/stdc++.h>
typedef long long LL;

const int N = 4000 + 5;
const int MOD = (int)1e9 + 7;

int F[N + N],Finv[N + N],Inv[N + N];
int n;

void init() {
    Inv[1] = 1;
    for (int i = 2; i < N + N; ++ i) {
        Inv[i] = (MOD - MOD / i) * 1ll * Inv[MOD % i] % MOD;
    }

    F[0] = Finv[0] = 1;
    for (int i = 1; i < N + N; ++ i) {
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
}

int dp[N][2];

int work() {
    dp[0][0] = 1;
    for (int i = 0; i < n; ++ i) {
        for (int j = 0; j < 2; ++ j) {
            if (dp[i][j] == 0) continue;
            for (int k = 1; i + k <= n; ++ k) {
                add(dp[i + k][j],dp[i][j] * 1ll * comb(n - i - 1,k - 1) % MOD);
            }
            add(dp[i + 1][1],dp[i][j]);
        }
    }
    return dp[n][1];
}

int main() {
    init();
    scanf("%d",&n);
    printf("%d\n",work());
}
