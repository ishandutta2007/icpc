#include <bits/stdc++.h>

const int N = 1000000 + 5;
const int MOD = (int)1e9 + 7;
int Inv[N],Finv[N],F[N];
int n;

int comb(int a,int b) {
    if (b < 0 || b > a) return 0;
    return F[a] * 1ll * Finv[b] % MOD * Finv[a - b] % MOD;
}

int main() {
    Inv[1] = 1;
    for (int i = 2; i < N; ++ i)
        Inv[i] = (MOD - MOD / i) * 1ll * Inv[MOD % i] % MOD;
    F[0] = Finv[0] = 1;
    for (int i = 1; i < N; ++ i) {
        F[i] = F[i - 1] * 1ll * i % MOD;
        Finv[i] = Finv[i - 1] * 1ll * Inv[i] % MOD;
    }
    scanf("%d",&n);
    int answer = 0;
    for (int i = 1; i <= n + 1; ++ i) {
        answer = (answer + comb(n + 1,i) * 1ll * comb(n + 1,i) % MOD) % MOD;
    }
    printf("%d\n",answer);
}
