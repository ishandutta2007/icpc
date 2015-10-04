#include <bits/stdc++.h>

const int N = 2000 + 5;
const int MOD = 258280327;
int q_pow[N];
int n;
int dp[N][N];

int inv(int x) {
    return x == 1 ? 1 : (MOD - MOD / x) * 1ll * inv(MOD % x) % MOD;
}

inline void add(int &a,int b) {
    a += b;
    if (a >= MOD) a -= MOD;
}

void work() {
    for (int i = 0; i < n; ++ i) {
        for (int j = 0; j < n; ++ j) {
            dp[i][j] = 0;
        }
    }
    dp[0][0] = 1;
    for (int i = 0; i < n; ++ i) {
        for (int j = 0; j < n; ++ j) {
            add(dp[i + 1][j + 1],dp[i][j] * 1ll * q_pow[j] % MOD);
            add(dp[i + 1][j],dp[i][j] * 1ll * (MOD + 1 - q_pow[j]) % MOD);
        }
    }
    for (int i = 0; i < n; ++ i) {
        int val = 0;
        for (int j = 0; j < n; ++ j) {
            add(val,dp[j][i]);
        }
        val = val * 1ll * q_pow[i] % MOD * inv(n) % MOD;
        if (i) putchar(' ');
        printf("%d",val);
    }
    puts("");
}

int main() {
    int cas;
    scanf("%d",&cas);
    while (cas--) {
        int x,y;
        scanf("%d%d%d",&n,&x,&y);
        int q = (1 + MOD - x * 1ll * inv(y) % MOD) % MOD;
        q_pow[0] = 1;
        for (int i = 1; i < N; ++ i) {
            q_pow[i] = q_pow[i - 1] * 1ll * q % MOD;
        }
        work();
    }
}
