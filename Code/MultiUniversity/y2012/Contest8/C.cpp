#include <bits/stdc++.h>

const int MOD = (int)1e9 + 7;
const int N = 2000 + 5;
int comb[N][N];
int stirling[N][N];

inline void add(int &a,int b) {
    a += b;
    if (a >= MOD) a -= MOD;
}

void init(int n) {
    for (int i = 0; i <= n; ++ i) {
        comb[i][i] = comb[i][0] = 1;
        for (int j = 1; j < i; ++ j) {
            comb[i][j] = comb[i - 1][j] + comb[i - 1][j - 1];
            if (comb[i][j] >= MOD)
                comb[i][j] -= MOD;
        }
    }
    stirling[0][0] = 1;
    for (int i = 0; i <= n; ++ i) {
        for (int j = 0; j <= i; ++ j) {
            add(stirling[i + 1][j],stirling[i][j] * 1ll * i % MOD);
            add(stirling[i + 1][j + 1],stirling[i][j]);
        }
    }
}

int n,f,b;

int work() {
    if (f + b - 1 > n) return 0;
    return stirling[n - 1][f - 1 + b - 1] * 1ll * comb[f - 1 + b - 1][f - 1] % MOD;
}

int main() {
    init(2000);
    int cas;
    scanf("%d",&cas);
    while (cas--) {
        scanf("%d%d%d",&n,&f,&b);
        printf("%d\n",work());
    }
}
