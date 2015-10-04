#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <vector>

const int LOG = 18;
const int N = 100000 + 5;
int plca[N][LOG];
int n,m;
std::vector<int> edges[N];
int que[N];
std::vector<std::pair<std::pair<int,int>,int> > paths[N];
int depth[N];
int dsu[N];
int SS[N],WW[N];
int S[N],W[N];

int Find(int x) {
    int y = x;
    std::vector<int> stack;
    while (y != dsu[y]) {
        stack.push_back(y);
        y = dsu[y];
    }
    for (int i = (int)stack.size() - 1; i >= 0; -- i) {
        int u = stack[i];
        int v = y;
        if (i + 1 != stack.size()) {
            v = stack[i + 1];
        }
        if (dsu[u] != y) {
            SS[u] += SS[v];
            WW[u] += WW[v];
        }
        dsu[u] = y;
    }
    return y;
}

int work() {
    for (int i = 0; i < n; ++ i) {
        dsu[i] = i;
    }
    for (int I = n - 1; I >= 0; -- I) {
        int u = que[I];
        W[u] = WW[u] = S[u] = SS[u] = 0;
        for (int i = 0; i < edges[u].size(); ++ i) {
            int v = edges[u][i];
            if (v == plca[u][0]) continue;
            S[u] += W[v];
            W[u] += W[v];
            dsu[v] = u;
        }
        for (int i = 0; i < paths[u].size(); ++ i) {
            int a = paths[u][i].first.first;
            int b = paths[u][i].first.second;
            int c = paths[u][i].second;
            int tmp = 0;
            Find(a);
            Find(b);
            tmp += SS[a];
            tmp += SS[b];
            tmp += S[u];
            if (a != u) {
                tmp -= WW[a];
            }
            if (b != u) {
                tmp -= WW[b];
            }
            tmp += c;
            W[u] = std::max(W[u],tmp);
        }
        W[u] = std::max(W[u],S[u]);
        WW[u] = W[u];
        SS[u] = S[u];
    }
    return W[0];
}

void prepare() {
    int qf = 0,qe = 0;
    que[qe++] = 0;
    plca[0][0] = -1;
    while (qf != qe) {
        int u = que[qf++];
        for (int i = 1; i < LOG; ++ i) {
            plca[u][i] = -1;
            if (plca[u][i - 1] != -1) {
                plca[u][i] = plca[plca[u][i - 1]][i - 1];
            }
        }
        for (int i = 0; i < edges[u].size(); ++ i) {
            int v = edges[u][i];
            if (v == plca[u][0]) continue;
            depth[v] = depth[u] + 1;
            plca[v][0] = u;
            que[qe++] = v;
        }
    }
}

int get_lca(int a,int b) {
    if (depth[a] < depth[b]) std::swap(a,b);
    for (int i = 0; i < LOG; ++ i) {
        if (depth[a] - depth[b] >> i & 1) {
            a = plca[a][i];
        }
    }
    if (a == b) return a;
    for (int i = LOG - 1; i >= 0; -- i) {
        if (plca[a][i] != plca[b][i]) {
            a = plca[a][i];
            b = plca[b][i];
        }
    }
    return plca[a][0];
}

int main() {
    int cas;
    scanf("%d",&cas);
    while (cas--) {
        scanf("%d%d",&n,&m);
        for (int i = 0; i < n; ++ i) {
            edges[i].clear();
            paths[i].clear();
        }
        for (int i = 0; i < n - 1; ++ i) {
            int a,b;
            scanf("%d%d",&a,&b); a --; b --;
            edges[b].push_back(a);
            edges[a].push_back(b);
        }
        prepare();
        for (int i = 0; i < m; ++ i) {
            int a,b,c;
            scanf("%d%d%d",&a,&b,&c); a --; b --;
            int lca = get_lca(a,b);
            paths[lca].push_back(std::make_pair(std::make_pair(a,b),c));
        }
        printf("%d\n",work());
    }
}
