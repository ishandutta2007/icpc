#include <bits/stdc++.h>

const int MOD = (int)1e9 + 7;
const int N = 300000 + 5;

int F[N],Finv[N],Inv[N];
int h,w,n,X[2000],Y[2000];
bool vis[2000];
int ways[2000];

int comb(int a,int b) {
    if (b < 0 || b > a) return 0;
    return F[a] * 1ll * Finv[b] % MOD * Finv[a - b] % MOD;
}

int f(int a,int b,int c,int d) {
    int x = c - a;
    int y = d - b;
    assert(x >= 0 && y >= 0);
    return comb(x + y,x);
}

inline void add(int &a,int b) {
    a += b;
    if (a >= MOD) a -= MOD;
    if (a < 0) a += MOD;
}

void calc(int id) {
    if (vis[id]) return ;
    vis[id] = true;
    ways[id] = f(1,1,X[id],Y[id]);
    for (int i = 0; i < n; ++ i) {
        if (X[i] <= X[id] && Y[i] <= Y[id] && i != id) {
            calc(i);
            add(ways[id],MOD - ways[i] * 1ll * f(X[i],Y[i],X[id],Y[id]) % MOD);
        }
    }
}

int work() {
    for (int i = 0; i < n; ++ i) {
        if (!vis[i]) {
            calc(i);
        }
    }
    int ret = f(1,1,h,w);
    for (int i = 0; i < n; ++ i) {
        add(ret,MOD - ways[i] * 1ll * f(X[i],Y[i],h,w) % MOD);
    }
    return ret;
}

int main() {
    Inv[1] = 1;
    for (int i = 2; i < N; ++ i) {
        Inv[i] = (MOD - MOD / i) * 1ll * Inv[MOD % i] % MOD;
    }
    F[0] = Finv[0] = 1;
    for (int i = 1; i < N; ++ i) {
        F[i] = F[i - 1] * 1ll * i % MOD;
        Finv[i] = Finv[i - 1] * 1ll * Inv[i] % MOD;
    }
    scanf("%d%d%d",&h,&w,&n);
    for (int i = 0; i < n; ++ i) {
        scanf("%d%d",X + i,Y + i);
    }
    printf("%d\n",work());
}
