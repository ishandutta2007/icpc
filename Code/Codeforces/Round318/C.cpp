#include <bits/stdc++.h>

const int N = 100000 + 5;
std::vector<int> edges[N];
int n;
bool del[N];
int leg[N];

void dfs(int u) {
    if (del[u]) return ;
    del[u] = true;
    for (int v : edges[u]) {
        if (edges[v].size() <= 2)
            dfs(v);
    }
}

bool work() {
    for (int u = 0; u < n; ++ u) {
        if (edges[u].size() == 1)
            dfs(u);
    }
    for (int u = 0; u < n; ++ u) {
        for (int v : edges[u]) {
            if (del[v])
                leg[u] = std::min(leg[u] + 1,2);
        }
    }
    for (int u = 0; u < n; ++ u) {
        int cnt = 0;
        for (int v : edges[u]) {
            if ((int)edges[v].size() - leg[v] > 1)
                ++ cnt;
        }
        if (cnt > 2)
            return false;
    }
    return true;
}

int main() {
    scanf("%d",&n);
    for (int i = 0; i < n - 1; ++ i) {
        int a,b;
        scanf("%d%d",&a,&b); a --; b --;
        edges[a].push_back(b);
        edges[b].push_back(a);
    }
    puts(work() ? "Yes" : "No");
}
