#include <stdio.h>

const int N = 100 + 5;
const int MOD = (int)1e9 + 7;
int n,K,m;
int prob[N][N][N][2];
int dp[N][N][N];
bool isp[N];
int cnt[N];

inline void add(int &a,int b) {
    a += b;
    if (a >= MOD) a -= MOD;
}

int A[N][N][N],D[N][N][N];

int Inv[N];

int work() {
    for (int k = 0; k <= n; ++ k) {
        for (int i = 1; i <= n; ++ i) {
            A[k][i][i - 1] = 1;
            for (int j = i; j <= n; ++ j) {
                if (isp[j])
                    A[k][i][j] = A[k][i][j - 1] * 1ll * Inv[cnt[j] + k] % MOD;
                else
                    A[k][i][j] = A[k][i][j - 1];
            }
            D[k][i + 1][i] = 1;
            for (int j = i; j >= 1; -- j) {
                if (isp[j])
                    D[k][j][i] = D[k][j + 1][i] * 1ll * Inv[cnt[j] + k + 1] % MOD;
                else
                    D[k][j][i] = D[k][j + 1][i];
            }
        }
    }
    for (int k = 0; k <= n - m; ++ k) {
        for (int i = 1; i <= n; ++ i) {
            if (k > cnt[i - 1]) continue;
            for (int j = i; j <= n; ++ j) {
                int t = j - i + 1 - cnt[j] + cnt[i - 1];
                int b = t * (t - 1) / 2;
                prob[k][i][j][0] = A[k][i][j] * 1ll * Inv[2] % MOD * b % MOD;
                prob[k][i][j][1] = 0;
                int c = 0;
                for (int r = j; r >= i; -- r) {
                    if (isp[r]) {
                        add(prob[k][i][j][1],c * 1ll * D[k][r][j] % MOD
                                * A[k][i][r - 1] % MOD);
                    } else {
                        c ++;
                    }
                }
                c = 0;
                for (int r = i; r <= j; ++ r) {
                    if (!isp[r]) {
                        c ++;
                    } else {
                        add(prob[k][i][j][0],c * 1ll * A[k][i][j] % MOD);
                        add(prob[k][i][j][1],MOD - c * 1ll * A[k][i][r - 1] % MOD
                                * D[k][r][j] % MOD);
                    }
                }
            }
        }
    }
    for (int i = 0; i <= K; ++ i) {
        for (int j = 0; j <= n - m; ++ j) {
            for (int k = 0; k <= n; ++ k) {
                dp[i][j][k] = 0;
            }
        }
    }
    dp[0][0][0] = 1;
    for (int i = 0; i < K; ++ i) {
        for (int j = 0; j <= n - m; ++ j) {
            for (int k = 0; k < n; ++ k) {
                if (dp[i][j][k] == 0) continue;
                for (int r = k + 2; r <= n; ++ r) {
                    add(dp[i + 1][j][r],dp[i][j][k] * 1ll * prob[j][k + 1][r][0] % MOD);
                    add(dp[i + 1][j + 1][r],dp[i][j][k] * 1ll * prob[j][k + 1][r][1] % MOD);
                }
            }
        }
    }
    int ret = 0;
    for (int i = 0; i <= n - m; ++ i) {
        add(ret,dp[K][i][n]);
    }
    for (int i = 1; i <= m; ++ i) {
        ret = ret * 1ll * i % MOD;
    }
    return ret;
}

int main() {
    Inv[1] = 1;
    for (int i = 2; i < N; ++ i) {
        Inv[i] = (MOD - MOD / i) * 1ll * Inv[MOD % i] % MOD;
    }
    while (scanf("%d%d%d",&n,&K,&m) == 3) {
        for (int i = 0; i <= n; ++ i) {
            isp[i] = false;
        }
        for (int i = 0; i < m; ++ i) {
            int x;
            scanf("%d",&x);
            isp[x] = true;
        }
        for (int i = 1; i <= n; ++ i) {
            cnt[i] = cnt[i - 1] + isp[i];
        }
        printf("%d\n",work());
    }
}

