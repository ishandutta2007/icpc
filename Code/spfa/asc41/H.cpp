#include <bits/stdc++.h>
using LL = long long ;

int n;
const int N = 100000 + 5;
std::vector<std::pair<int,int>> edges[N];
int P[N];
LL sum[N],dp[N];
LL optimal[N];

void dfs(int u,int fa) {
    sum[u] = P[u];
    for (auto t : edges[u]) {
        int v = t.first;
        int w = t.second;
        if (v == fa) continue;
        dfs(v,u);
        sum[u] += sum[v];
        dp[u] += dp[v] + sum[v] * w;
    }
}

void DFS(int u,int fa,LL val) {
    optimal[u] = dp[u] + val;
    for (auto t : edges[u]) {
        int v = t.first;
        int w = t.second;
        if (v == fa) continue;
        LL tmp = val;
        tmp += dp[u];
        tmp -= dp[v];
        tmp -= sum[v] * w;
        tmp += (sum[0] - sum[v]) * w;
        DFS(v,u,tmp);
    }
}

int main() {
    freopen("house.in","r",stdin);
    freopen("house.out","w",stdout);
    scanf("%d",&n);
    for (int i = 0; i < n; ++ i) {
        scanf("%d",P + i);
    }
    for (int i = 0; i < n - 1; ++ i) {
        int a,b,c;
        scanf("%d%d%d",&a,&b,&c); a --; b --;
        edges[a].emplace_back(b,c);
        edges[b].emplace_back(a,c);
    }
    dfs(0,-1);
    DFS(0,-1,0);
    int p = 0;
    for (int i = 0; i < n; ++ i) {
        if (optimal[p] > optimal[i]) {
            p = i;
        }
    }
    printf("%d %I64d\n",p + 1,optimal[p]);
}
