#include <bits/stdc++.h>
typedef long long LL;

const int MOD = (int)1e9 + 7;
int n,m,K;
int Inv[1000000 + 1];

int pow_mod(int a,int b) {
    int ret = 1;
    for ( ; b; b >>= 1) {
        if (b & 1) ret = ret * 1ll * a % MOD;
        a = a * 1ll * a % MOD;
    }
    return ret;
}

int f(int n,int k) {
    if (k == 0) return 0;
    return k * 1ll * pow_mod(k - 1,n - 1) % MOD;
}

int work() {
    LL ret = 0;
    for (int i = 1,c = 1; i <= K; ++ i) {
        c = c * 1ll * (K - i + 1) % MOD * Inv[i] % MOD;
        if (K - i & 1)
            ret -= c * 1ll * f(n,i) % MOD;
        else 
            ret += c * 1ll * f(n,i) % MOD;
    }
    ret = (ret % MOD + MOD) % MOD;
    for (int i = 1; i <= K; ++ i) {
        ret = ret * 1ll * (m - i + 1) % MOD * Inv[i] % MOD;
    }
    return ret;
}

int main() {
    Inv[1] = 1;
    for (int i = 2; i <= 1000000; ++ i)
        Inv[i] = (MOD - MOD / i) * 1ll * Inv[MOD % i] % MOD;
    int cas,ca = 0;
    scanf("%d",&cas);
    while (cas--) {
        scanf("%d%d%d",&n,&m,&K);
        printf("Case #%d: %d\n",++ca,work());
    }
}
