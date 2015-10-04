#include <bits/stdc++.h>

const int N = 20 + 5;
const int INF = 0x3f3f3f3f;
int n,m;
std::vector<std::pair<int,int>> e;
std::vector<int> W,P,edges[N];
int dfn[N];

bool dfs(int u,int c) {
    if (dfn[u] != -1) {
        return dfn[u] == c;
    }
    dfn[u] = c;
    if (P[u] != 2 && dfn[u] != P[u]) {
        return false;
    }
    for (auto t : edges[u]) {
        if (!dfs(t,c ^ 1))
            return false;
    }
    return true;
}

int work() {
    int ret = INF;
    for (int mask = 0; mask < 1 << n; ++ mask) {
        int cost = 0;
        std::vector<int> col(n,-1);
        for (int i = 0; i < n; ++ i) {
            if (mask >> i & 1) {
                cost += W[i];
            } 
        }
        if (cost >= ret) continue;
        std::fill(edges,edges + n,std::vector<int>());
        bool flag = true;
        for (auto t : e) {
            int a = t.first;
            int b = t.second;
            if ((mask >> a & 1) || (mask >> b & 1)) continue;
            edges[a].push_back(b);
            edges[b].push_back(a);
        }
        memset(dfn,-1,sizeof(dfn));
        for (int i = 0; i < n; ++ i) {
            if (dfn[i] == -1 && P[i] != 2) {
                flag &= dfs(i,P[i]);
            }
        }
        if (flag) {
            ret = cost;
        }
    }
    return ret;
}

int main() {
//    freopen("G.data","r",stdin);
//    freopen("G_brute.out","w",stdout);
    while (scanf("%d%d",&n,&m) == 2) {
        W.clear();
        P.clear();
        e.clear();
        for (int i = 0; i < n; ++ i) {
            int x;
            scanf("%d",&x);
            W.push_back(x);
        }
        for (int i = 0; i < n; ++ i) {
            int x;
            scanf("%d",&x);
            P.push_back(x - 1);
        }
        for (int i = 0; i < m; ++ i) {
            int a,b;
            scanf("%d%d",&a,&b);
            e.emplace_back(a - 1,b - 1);
        }
        printf("%d\n",work());
    }
}
