#include <stdio.h>
#include <string.h>
#include <algorithm>

const int N = 100000 + 5;
const int D = 101 + 5;
const int INF = 0x3f3f3f3f;
int n;
std::vector<int> edges[N];
int W[N];
int f[N][D],F[N][D],g[N][D],G[N][D];
int que[N];

int work() {
    int qf = 0,qe = 0;
    que[qe++] = 0;
    while (qf != qe) {
        int u = que[qf++];
        for (int v : edges[u]) {
            que[qe++] = v;
            edges[v].erase(std::find(edges[v].begin(),edges[v].end(),u));
        }
    }
    for (int I = n - 1; I >= 0; -- I) {
        int u = que[I];
        for (int i = 0; i < D; ++ i) {
            f[u][i] = F[u][i] = G[u][i] = g[u][i] = INF;
        }
        {
            int a = 0;
            for (int v : edges[u]) {
                a += f[v][0];
                if (a > INF) a = INF;
            }
            g[u][0] = std::min(g[u][0],a);
        }
        for (int i = 1; i < D; ++ i) {
            int a = 0,b = INF;
            for (int v : edges[u]) {
                int tmp = std::min(G[v][i - 1],F[v][i]);
                b = std::min(b,g[v][i - 1] - tmp);
                a += tmp;
                if (a > INF) a = INF;
            }
            g[u][i] = std::min(g[u][i],a + b);
        }
        for (int i = 0; i + 1 < D; ++ i) {
            int a = 0,b = INF;
            for (int v : edges[u]) {
                int tmp = F[v][i + 1];
                if (i > 0) {
                    tmp = std::min(tmp,G[v][i - 1]);
                }
                b = std::min(b,f[v][i + 1] - tmp);
                a += tmp;
                if (a > INF) a = INF;
            }
            f[u][i] = std::min(f[u][i],a + b);
            if (i == W[u]) {
                f[u][i] = std::min(f[u][i],a + 1);
            }
        }
        f[u][W[u]] = std::min(f[u][W[u]],g[u][0] + 1);

        F[u][0] = f[u][0];
        G[u][0] = g[u][0];
        for (int i = 1; i < D; ++ i) {
            F[u][i] = std::min(F[u][i - 1],f[u][i]);
            G[u][i] = std::min(G[u][i - 1],g[u][i]);
        }
    }
    return F[0][D - 1];
}

int main() {
    while (scanf("%d",&n) == 1) {
        for (int i = 0; i < n; ++ i) {
            scanf("%d",W + i);
        }
        for (int i = 0; i < n; ++ i) {
            edges[i].clear();
        }
        for (int i = 0; i < n - 1; ++ i) {
            int a,b;
            scanf("%d%d",&a,&b); a --; b --;
            edges[a].push_back(b);
            edges[b].push_back(a);
        }
        printf("%d\n",work());
    }
}
