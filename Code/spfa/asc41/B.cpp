#include <bits/stdc++.h>

const int N = 100000 + 5;
std::vector<int> edges[N];
std::set<int> ban[N];
int n,m;
std::vector<int> single;
int col[N];
int parent[N];

void work() {
    m = n / 2 + 1;
    for (int i = m - 1; i >= 1; -- i) {
        single.push_back(i);
    }
    memset(col,-1,sizeof(col));
    col[0] = 0;
    parent[0] = -1;
    std::queue<int> que;
    que.push(0);
    std::set<int> set;
    for (int i = 0; i < m; ++ i) {
        set.insert(i);
    }
    for (int i = 0; i < m; ++ i) {
        ban[i].insert(i);
    }
    while (!que.empty()) {
        int u = que.front(); que.pop();
        auto it = set.begin();
        for (int v : edges[u]) {
            if (v == parent[u]) continue;
            que.push(v);
            parent[v] = u;
            if (!single.empty()) {
                col[v] = single.back();
                single.pop_back();
            } else {
                while (it != set.end() && ban[*it].find(col[u]) != ban[*it].end()) {
                    ++ it;
                }
                assert(it != set.end());
                col[v] = *it;
                set.erase(it++);
            }
            ban[col[u]].insert(col[v]);
            ban[col[v]].insert(col[u]);
        }
    }
}

int main() {
    freopen("bicoloring.in","r",stdin);
    freopen("bicoloring.out","w",stdout);
    scanf("%d",&n);
    for (int i = 0; i < n - 1; ++ i) {
        int a,b;
        scanf("%d%d",&a,&b); a --; b --;
        edges[a].push_back(b);
        edges[b].push_back(a);
    }
    work();
    for (int i = 0; i < n; ++ i) {
        if (i) putchar(' ');
        printf("%d",col[i] + 1);
    }
    puts("");
}
