#include <bits/stdc++.h>

const int N = 10000 + 5;
std::vector<int> edges[N];
int A[N],B[N];
int n;

void dfs(int u,int fa) {
    std::vector<std::pair<int,int>> vec;
    for (int v : edges[u]) {
        if (v == fa) continue;
        dfs(v,u);
        vec.push_back({B[v] - A[v],v});
    }
    std::sort(vec.begin(),vec.end());
    int tmp = A[u];
    A[u] = B[u];
    for (auto t : vec) {
        int v = t.second;
        tmp = std::max(tmp,A[u] + A[v]);
        A[u] += B[v];
    }
    B[u] = A[u];
    A[u] = tmp;
}

int work() {
    dfs(0,-1);
    return A[0];
}

int main() {
    scanf("%d",&n);
    for (int i = 0; i < n; ++ i) {
        scanf("%d%d",A + i,B + i);
        B[i] = A[i] - B[i];
    }
    for (int i = 0; i < n - 1; ++ i) {
        int a,b;
        scanf("%d%d",&a,&b); a --; b --;
        edges[a].push_back(b);
        edges[b].push_back(a);
    }
    printf("%d\n",work());
}

