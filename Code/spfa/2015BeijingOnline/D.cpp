#include <bits/stdc++.h>

const int MOD = (int)1e9 + 7;
const int inv2 = MOD + 1 >> 1;

void fwt(int A[],int n,int inv) {
    for (int l = 1; l << 1 <= n; l <<= 1) {
        for (int s = 0; s < n; ++ s) {
            if (~s & l) {
                int a = A[s],b = A[s ^ l];
                if (inv == 1) {
                    A[s] = (a - b + MOD) % MOD;
                    A[s ^ l] = (a + b) % MOD;
                } else {
                    A[s] = (a + b) * 1ll * inv2 % MOD;
                    A[s ^ l] = (b - a + MOD) * 1ll * inv2 % MOD;
                }
            }
        }
    }
}

int n,m,l,r,A[1 << 11];

int pow_mod(int a,int b) {
    int ret = 1;
    for ( ; b; b >>= 1) {
        if (b & 1) ret = ret * 1ll * a % MOD;
        a = a * 1ll * a % MOD;
    }
    return ret;
}

int work() {
    n = n << 1 | 1;
    int ret = 0;
    for (int x = l; x <= r; ++ x) {
        memset(A,0,sizeof(A));
        for (int i = x; i <= x + m; ++ i) {
            A[i] = 1;
        }
        fwt(A,1 << 11,1);
        for (int i = 0; i < 1 << 11; ++ i) {
            A[i] = pow_mod(A[i],n);
        }
        fwt(A,1 << 11,-1);
        ret = (ret + A[0]) % MOD;
    }
    return ret;
}

int main() {
    while (scanf("%d%d%d%d",&n,&m,&l,&r) == 4) {
        printf("%d\n",work());
    }
}
