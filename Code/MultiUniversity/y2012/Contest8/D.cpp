#include <bits/stdc++.h>

int exgcd(int a,int b,int &x,int &y) {
    if (b == 0) {
        return x = 1,y = 0,a;
    } else {
        int g = exgcd(b,a % b,y,x);
        y -= a / b * x;
        return g;
    }
}

// n¸ö·½³Ì £¬ x = a[i] (mod m[i])
int china(int n, int a[], int m[]) {
    int M = 1;
    for(int i = 0; i < n; ++ i) M *= m[i];
    int ret = 0;
    for(int i = 0;i < n; i++) {
        int w = M / m[i],x,y;
        int d = exgcd(w,m[i],x,y);
        ret = (ret + x * 1ll * w  % M * a[i] % M) % M;
    }
    return (ret + M) % M;
}

int pow_mod(int a,int b,int p) {
    int ret = 1 % p; 
    for ( ; b; b >>= 1) { 
        if (b & 1) ret = ret * 1ll * a % p;
        a = a * 1ll * a % p;
    }
    return ret;
}

int inv(int x,int p) {
    return pow_mod(x,p - 2,p);
}

int n,m,K,A[15];
int mod[2] = {97,3761599};
const int N = 1100000 + 5;
int F[2][N],Finv[2][N];

int comb(int a,int b,int i) {
    if (b < 0 || b > a) return 0;
    return F[i][a] * 1ll * Finv[i][a - b] % mod[i] * Finv[i][b] % mod[i];
}

int lucas(int a,int b,int i) {
    if (a == 0 && b == 0) return 1;
    if (b < 0 || b > a) return 0;
    return lucas(a / mod[i],b / mod[i],i) * 1ll * comb(a % mod[i],b % mod[i],i) % mod[i];
}

int solve(int id) {
    int ret = 1;
    for (int i = 0; i < K; ++ i) {
        int l = -A[i];
        if (i == K - 1)
            l += m;
        else
            l += A[i + 1];
        ret = ret * 1ll * lucas(n + l - 1,l,id) % mod[id];
    }
    return ret;
}

int work() {
    int a[2] = {solve(0),solve(1)};
    return china(2,a,mod);
}

int main() {
    F[0][0] = F[1][0] = Finv[0][0] = Finv[1][0] = 1;
    for (int i = 0; i < 2; ++ i) {
        for (int  j = 1; j < N; ++ j) {
            F[i][j] = F[i][j - 1] * 1ll * j % mod[i];
            Finv[i][j] = Finv[i][j - 1] * 1ll * inv(j,mod[i]) % mod[i];
        }
    }
    int cas,ca = 0;
    scanf("%d",&cas);
    while (cas--) {
        scanf("%d%d",&n,&m);
        scanf("%d",&K);
        for (int i = 0; i < K; ++ i) {
            scanf("%d",A + i);
        }
        printf("Case #%d: %d\n",++ca,work());
    }
}

