#include <bits/stdc++.h>
typedef long long LL;

const int N = 100000 + 5;
const int LOG = 18;
int n;
std::vector<std::pair<int,int>> edges[N];
std::pair<int,int> D[N];
int plca[N][LOG];
LL dis[N];
int depth[N];
int weight[N];

void dfs(int u,int fa) {
    plca[u][0] = fa;
    for (int i = 1; i < LOG; ++ i) {
        plca[u][i] = -1;
        if (plca[u][i - 1] != -1) {
            plca[u][i] = plca[plca[u][i - 1]][i - 1];
        }
    }
    for (auto t : edges[u]) {
        int v = t.first;
        int w = t.second;
        if (v == fa) continue;
        depth[v] = depth[u] + 1;
        dis[v] = dis[u] + w;
        dfs(v,u);
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

LL get_dis(int a,int b) {
    return dis[a] + dis[b] - 2 * dis[get_lca(a,b)];
}

int dsu[N];
int A[N],B[N];
bool vis[N];

LL answer;

int Find(int x) {
    return dsu[x] == x ? x : dsu[x] = Find(dsu[x]);
}

LL combine(int u,int v) {
    if (plca[u][0] == v) {
        std::swap(u,v);
    }
    int s = Find(u);
    int t = Find(v);
    if (s == t) {
        return 0;
    }
    int l = A[s];
    int r = B[s];
    int tmp[4] = {A[s],B[s],A[t],B[t]};
    for (int i = 0; i < 4; ++ i) {
        for (int j = i + 1; j < 4; ++ j) {
            if (get_dis(tmp[i],tmp[j]) > get_dis(l,r)) {
                l = tmp[i];
                r = tmp[j];
            }
        }
    }
    dsu[s] = t;
    A[t] = l;
    B[t] = r;
    return get_dis(l,r);
}

void merge(int u) {
    for (auto t : edges[u]) {
        int v = t.first;
        int w = t.second;
        if (!vis[v]) continue;
        answer = std::max(answer,combine(u,v) * weight[u]);
    }
}

LL work() {
    dfs(0,-1);
    for (int i = 0; i < n; ++ i) {
        A[i] = B[i] = dsu[i] = i;
        vis[i] = false;
    }
    answer = 0;
    for (int i = n - 1,j = n - 2; i >= 0; i = j --) {
        while (j >= 0 && D[j].first == D[i].first) -- j;
        for (int k = j + 1; k <= i; ++ k) {
            merge(D[k].second);
            vis[D[k].second] = true;
        }
    }
    return answer;
}

int main() {
    int cas;
    scanf("%d",&cas);
    while (cas--) {
        scanf("%d",&n);
        for (int i = 0; i < n; ++ i) {
            edges[i].clear();
        }
        for (int i = 0; i < n; ++ i) {
            int d;
            scanf("%d",&d);
            weight[i] = d;
            D[i] = {d,i};
        }
        std::sort(D,D + n);
        for (int i = 0; i < n - 1; ++ i) {
            int a,b,c;
            scanf("%d%d%d",&a,&b,&c); a --; b --;
            edges[a].push_back({b,c});
            edges[b].push_back({a,c});
        }
        printf("%lld\n",work());
    }
}
