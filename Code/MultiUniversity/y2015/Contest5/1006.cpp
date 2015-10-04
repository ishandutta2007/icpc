#pragma comment(linker, "/STACK:1024000000,1024000000")
#include <stdio.h>
#include <string.h>
#include <algorithm>

const int N = 100000 + 5;
int head[N],etot;
struct Edge {
    int v,next;
} g[1000000 + 5];

bool mark[N];
bool vis[1000000 + 5];
int degree[N];
int n,m;
int answer[1000000 + 5];

void add_edge(int u,int v) {
    g[etot].v = v; g[etot].next = head[u]; head[u] = etot ++;
}

void dfs(int u) {
    mark[u] = true;
    for (int &i = head[u]; i != -1; ) {
        int v = g[i].v;
        int t = i;
        i = g[i].next;
        if (vis[t >> 1]) continue;
        vis[t >> 1] = true;
        answer[t >> 1] = t & 1;
        dfs(v);
    }
}

void work() {
    int p = -1;
    for (int i = 0; i < n; ++ i) {
        if (degree[i] & 1) {
            if (p == -1) {
                p = i;
            } else {
                add_edge(i,p);
                add_edge(p,i);
                p = -1;
            }
        }
    }
    std::fill(mark,mark + n,false);
    std::fill(vis,vis + etot / 2,false);
    for (int i = 0; i < n; ++ i) {
        if (!mark[i]) {
            dfs(i);
        }
    }
    for (int i = 0; i < m; ++ i) {
        printf("%d\n",answer[i]);
    }
}

int main() {
    int cas;
    scanf("%d",&cas);
    while (cas--) {
        scanf("%d%d",&n,&m);
        std::fill(head,head + n,-1); etot = 0;
        std::fill(degree,degree + n,0);
        for (int i = 0; i < m; ++ i) {
            int a,b;
            scanf("%d%d",&a,&b); a --; b --;
            degree[a] ++;
            degree[b] ++;
            add_edge(a,b);
            add_edge(b,a);
        }
        work();
    }
}
