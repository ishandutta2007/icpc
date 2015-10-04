#include <bits/stdc++.h>
typedef long long LL;

const int MOD = 998244353;
const int inv2 = MOD + 1 >> 1;

bool graph[16][16];
int n,m;
int dp[1 << 16][16];
int ways[1 << 16];
int g[16][16];
int map[16];

inline void add(int &a,int b) {
    a += b;
    if (a >= MOD) a -= MOD;
}

int det(int A[16][16],int n) {
    int ret = 1;
    for (int i = 0; i < n; ++ i) {
        if (A[i][i] == 0) {
            for (int j = i + 1; j < n; ++ j) {
                if (A[j][i]) {
                    for (int k = i; k < n; ++ k) {
                        std::swap(A[i][k],A[j][k]);
                    }
                    ret = -ret;
                    break;
                }
            }
            if (A[i][i] == 0) return 0;
        }
        for (int j = i + 1; j < n; ++ j) {
            int a = 1,b = 0,c = 0,d = 1;
            int x = A[i][i],y = A[j][i];
            while (y) {
                int t = x / y;
                if (t < 0) t += MOD;
                add(a,MOD - c * 1ll * t % MOD);
                add(b,MOD - d * 1ll * t % MOD);
                std::swap(a,c);
                std::swap(b,d);
                x %= y;
                std::swap(x,y);
                ret = -ret;
            }
            for (int k = 0; k < n; ++ k) {
                int q = A[i][k],w = A[j][k];
                A[i][k] = (a * 1ll * q + b * 1ll * w) % MOD;
                A[j][k] = (c * 1ll * q + d * 1ll * w) % MOD;
            }
        }
        ret = A[i][i] * 1ll * ret % MOD;
    }
    if (ret < 0) {
        ret += MOD;
    }
    return ret;
}

int work() {
    for (int mask = 0; mask < 1 << n; ++ mask) {
        for (int u = 0; u < n; ++ u) {
            dp[mask][u] = 0;
        }
    }
    for (int i = 0; i < n; ++ i) {
        dp[1 << i][i] = 1;
    }
    for (int mask = 0; mask < 1 << n; ++ mask) {
        for (int u = 0; u < n; ++ u) {
            if (dp[mask][u] == 0) continue;
            for (int v = 0; mask >> v; ++ v) {
                if ((mask >> v & 1) == 0 && graph[u][v]) {
                    add(dp[mask ^ 1 << v][v],dp[mask][u]);
                }
            }
        }
    }
    for (int mask = 0; mask < 1 << n; ++ mask) {
        ways[mask] = 0;
        if (__builtin_popcount(mask) < 3) continue;
        int s = 0;
        while (mask >> s + 1) ++ s;
        for (int u = 0; mask >> u; ++ u) {
            if (dp[mask][u] && graph[u][s]) {
                add(ways[mask],dp[mask][u]);
            }
        }
    }
    int ret = 0;
    for (int mask = 0; mask < 1 << n; ++ mask) {
        if (ways[mask] == 0) continue;
        int tot = 1;
        for (int i = 0; i < n; ++ i) {
            if (mask >> i & 1) {
                map[i] = 0;
            } else {
                map[i] = tot ++;
            }
        }
        for (int i = 0; i < tot; ++ i) {
            for (int j = 0; j < tot; ++ j) {
                g[i][j] = 0;
            }
        }
        for (int i = 0; i < n; ++ i) {
            for (int j = 0; j < n; ++ j) {
                if (map[i] != map[j] && graph[i][j]) {
                    g[map[i]][map[j]] --;
                    g[map[i]][map[i]] ++;
                }
            }
        }
        add(ret,det(g,tot - 1) * 1ll * ways[mask] % MOD);
    }
    return ret * 1ll * inv2 % MOD;
}


int main() {
    //freopen("1005_std.in","r",stdin);
    //freopen("1005.out","w",stdout);
    while (scanf("%d%d",&n,&m) == 2) {
        memset(graph,0,sizeof(graph));
        for (int i = 0; i < m; ++ i) {
            int a,b;
            scanf("%d%d",&a,&b); a --; b --;
            graph[a][b] = graph[b][a] = true;
        }
        printf("%d\n",work());
    }
    //fprintf(stderr,"%.10f\n",clock() * 1. / CLOCKS_PER_SEC);
}

