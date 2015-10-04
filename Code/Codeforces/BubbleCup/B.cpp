#include <bits/stdc++.h>
typedef long long LL;

const int MOD = (int)1e9 + 7;
const int N = 100000 + 5;
std::vector<std::pair<int,int>> edges[N];
int n;
int K;

int up[N],down[N];
int two[1000000 + 1];
LL answer;

std::vector<std::pair<int,int>> path[N];
bool vis[N];
int dsu[N];

int find(int x) {
    return x == dsu[x] ? x : dsu[x] = find(dsu[x]);
}

void get_lca(int u,int fa) {
    dsu[u] = u;
    for (auto t : edges[u]) {
        int v = t.first;
        if (v == fa) continue;
        get_lca(v,u);
        dsu[v] = u;
    }
    vis[u] = true;
    for (auto t : path[u]) {
        int v = t.first;
        int c = t.second;
        if (!vis[v]) continue;
        int lca = find(v);
        int a = u,b = v;
        if (c == -1) std::swap(a,b);
        up[a] ++;
        up[lca] --;
        down[b] ++;
        down[lca] --;
    }
}

void calc(int u,int fa) {
    for (auto t : edges[u]) {
        int v = t.first;
        int c = t.second;
        if (v == fa) continue;
        calc(v,u);
        up[u] += up[v];
        down[u] += down[v];
        if (c == 1) {
            answer += two[up[v]] - 1;
        } else if (c == -1) {
            answer += two[down[v]] - 1;
        }
    }
}

int main() {
    two[0] = 1;
    for (int i = 1; i <= 1000000; ++ i) {
        two[i] = two[i - 1] << 1;
        if (two[i] >= MOD) two[i] -= MOD;
    }
    scanf("%d",&n);
    for (int i = 0; i < n - 1; ++ i) {
        int a,b,c;
        scanf("%d%d%d",&a,&b,&c); a --; b --;
        edges[a].push_back({b,c});
        edges[b].push_back({a,-c});
    }
    scanf("%d",&K);
    int now = 0;
    for (int i = 0; i < K; ++ i) {
        int x;
        scanf("%d",&x); x --;
        path[now].push_back({x,1});
        path[x].push_back({now,-1});
        now = x;
    }
    get_lca(0,-1);
    calc(0,-1);
    printf("%I64d\n",(answer % MOD + MOD) % MOD);
}
