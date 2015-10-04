#include <string.h>
#include <algorithm>
#include <stdio.h>
#include <vector>

bool graph[500][500];
int count[500];
int deg[500];
int n,m;
bool mark[500];
int best;

void make(int u,int dt) {
    for (int i = 0; i < n; ++ i) {
        if (graph[u][i]) {
            count[i] += dt;
        }
    }
}

void search(int u,int cnt) {
    if (cnt >= best) {
        return ;
    }
    {
        bool flag = true;
        for (int i = 0; i < n; ++ i) {
            if (!mark[i] && count[i] != deg[i]) {
                flag = false;
                break;
            }
        }
        if (flag) {
            best = cnt;
            return ;
        }
    }

    while (u < n && (mark[u] || count[u] == deg[u])) ++ u;
    
    if (u >= n) {
        return ;
    }

    mark[u] = true;
    make(u,1);
    search(u + 1,cnt + 1);
    make(u,-1);
    mark[u] = false;

    std::vector<int> nei;
    for (int i = 0; i < n; ++ i) {
        if (!mark[i] && graph[u][i] == true) {
            nei.push_back(i);
        }
    }
    for (int i = 0; i < nei.size(); ++ i) {
        int v = nei[i];
        mark[v] = true;
        make(v,1);
    }
    search(u + 1,cnt + nei.size());
    for (int i = 0; i < nei.size(); ++ i) {
        int v = nei[i];
        make(v,-1);
        mark[v] = false;
    }
}

int work() {
    best = std::min(n,30);
    search(0,0);
    return best;
}

int main() {
    while (scanf("%d%d",&n,&m) == 2) {
        memset(graph,0,sizeof(graph));
        memset(count,0,sizeof(count));
        memset(deg,0,sizeof(deg));
        memset(mark,0,sizeof(mark));

        for (int i = 0; i < m; ++ i) {
            int a,b;
            scanf("%d%d",&a,&b); a --; b --;
            graph[a][b] = graph[b][a] = true;
            deg[a] ++;
            deg[b] ++;
        }

        printf("%d\n",work());
    }
}
