#include <bits/stdc++.h>

const int N = 100000 + 5;
std::vector<int> edges[N];
int n,m;
int col[N];

int dfs(int u,int fa,int cnt) {
    if (col[u]) {
        cnt ++;
    } else {
        cnt = 0;
    }
    if (cnt > m) return 0;
    if (u != 0 && edges[u].size() == 1) {
        return 1;
    }
    int ret = 0;
    for (int v : edges[u]) {
        if (v == fa) continue;
        ret += dfs(v,u,cnt);
    }
    return ret;
}

int work() {
    return dfs(0,-1,0);
}

int main() {
    scanf("%d%d",&n,&m);
    for (int i = 0; i < n; ++ i) {
        scanf("%d",col + i);
    }
    for (int i = 0; i < n - 1; ++ i) {
        int a,b;
        scanf("%d%d",&a,&b); a --; b --;
        edges[a].push_back(b);
        edges[b].push_back(a);
    }
    printf("%d\n",work());
}
