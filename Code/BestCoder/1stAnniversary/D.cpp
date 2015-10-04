#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <queue>
#include <vector>
#include <bitset>

const int N = 10000 + 5;
int n,m;
std::vector<int> edges[N];
std::vector<int> A;
bool vis[N];
int mark[N];

std::pair<int,int> bfs(int source) {
    std::queue<int> que;
    que.push(source);
    vis[source] = true;
    int c[2] = {};
    while (!que.empty()) {
        int u = que.front(); que.pop();
        c[mark[u]] ++;
        for (int i = 0; i < edges[u].size(); ++ i) {
            int v = edges[u][i];
            if (vis[v]) continue;
            mark[v] = mark[u] ^ 1;
            vis[v] = true;
            que.push(v);
        }
    }
    return std::make_pair(c[0],c[1]);
}

std::bitset<20001> bitset,all;
const int bal = 10000;

int work() {
    A.clear();
    for (int i = 0; i < n; ++ i) {
        vis[i] = false;
    }
    for (int i = 0; i < n; ++ i) {
        if (!vis[i]) {
            std::pair<int,int> t = bfs(i);
            int x = std::min(t.first,t.second);
            t.first -= x;
            t.second -= x;
            if (t.second == 0) {
                std::swap(t.first,t.second);
            }
            A.push_back(t.second);
        }
    }
    bitset.reset();
    bitset.set(bal);
    all.reset();
    for (int i = 0; i <= n; ++ i) {
        all.set(bal + i);
        all.set(bal - i);
    }
    for (int i = 0; i < A.size(); ++ i) {
        int t = A[i];
        bitset |= bitset << t | bitset >> t;
        bitset &= all;
    }
    int dt = -1;
    for (int i = 0; ; ++ i) {
        if (bitset[i + bal] == 1 || bitset[i - bal] == 1) {
            dt = i;
            break;
        }
    }
    int l = n - dt >> 1;
    int r = n - l;
    return l * r - m;
}

int main() {
    int cas;
    scanf("%d",&cas);
    while (cas--) {
        scanf("%d%d",&n,&m);
        for (int i = 0; i < n; ++ i) {
            edges[i].clear();
        }
        for (int i = 0; i < m; ++ i) {
            int a,b;
            scanf("%d%d",&a,&b); a --; b --;
            edges[a].push_back(b);
            edges[b].push_back(a);
        }
        printf("%d\n",work());
    }
}
