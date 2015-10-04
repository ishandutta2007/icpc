#include <bits/stdc++.h>
typedef long long LL;

const int N = 50000 + 5;
const int LOG = 18;
std::vector<int> edges[N];
int n;
int sz[N];
int plca[N][LOG];
int depth[N];
LL up[N],down[N];

void dfs(int u,int fa) {
    plca[u][0] = fa;
    for (int i = 1; i < LOG; ++ i) {
        plca[u][i] = plca[u][i - 1] == -1 ? -1 : plca[plca[u][i - 1]][i - 1];
    }
    depth[u] = fa == -1 ? 0 : depth[fa] + 1;
    sz[u] = 1;
    for (int v : edges[u]) {
        if (v == fa) continue;
        dfs(v,u);
        sz[u] += sz[v];
    }
}

int get_lca(int a,int b) {
    if (depth[a] < depth[b]) std::swap(a,b);
    for (int i = 0; i < LOG; ++ i) {
        if (depth[a] - depth[b] >> i & 1)
            a = plca[a][i];
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

void dfs2(int u,int fa) {
    up[u] = 2 * sz[u] - 1;
    down[u] = fa == -1 ? 0 : 2 * (n - sz[u]) - 1;
    if (fa != -1) {
        up[u] += up[fa];
        down[u] += down[fa];
    }
    for (int v : edges[u]) {
        if (v == fa) continue;
        dfs2(v,u);
    }
}

void prepare() {
    dfs(0,-1);
    dfs2(0,-1);
}

LL calc(int a,int b) {
    int lca = get_lca(a,b);
    LL ret = 0;
    ret += up[a] - up[lca];
    ret += down[b] - down[lca];
    return ret;
}

int main() {
    int cas;
    scanf("%d",&cas);
    while (cas--) {
        scanf("%d",&n);
        for (int i = 0; i < n; ++ i) {
            edges[i].clear();
        }
        for (int i = 0; i < n - 1; ++ i) {
            int a,b;
            scanf("%d%d",&a,&b);
            edges[a].push_back(b);
            edges[b].push_back(a);
        }
        prepare();
        int nq;
        scanf("%d",&nq);
        while (nq--) {
            int tot;
            scanf("%d",&tot);
            int pre = -1;
            LL answer = 0;
            for (int i = 0; i < tot + 1; ++ i) {
                int x;
                scanf("%d",&x);
                if (pre != -1) {
                    answer += calc(pre,x);
                }
                pre = x;
            }
            printf("%I64d.0000\n",answer);
        }
        if (cas) {
            puts("");
        }
    }
}
