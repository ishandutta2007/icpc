#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <vector>

bool graph[30][30];
int n,m;
int best;
int mark;
int degree[30];
int count[30];

void make(int u,int dt) {
    for (int i = 0; i < n; ++ i) {
        if (graph[u][i]) {
            count[i] += dt;
        }
    }
}

void search(int cur) {
    if (__builtin_popcount(mark) >= best) {
        return ;
    }
    {
        bool flag = true;
        for (int i = 0; i < n; ++ i) {
            if (!(mark >> i & 1) && count[i] != degree[i]) {
                flag = false;
                break;
            }
        }
        if (flag) {
            best = __builtin_popcount(mark);
            return ;
        }
    }
    if (cur >= n) {
        return ;
    }

    if ((mark >> cur & 1) || count[cur] == degree[cur]) {
        search(cur + 1);
        return ;
    }

    mark ^= 1 << cur;
    make(cur,1);
    search(cur + 1);
    make(cur,-1);
    mark ^= 1 << cur;

    std::vector<int> nei;
    for (int i = 0; i < n; ++ i) {
        if (graph[cur][i] && !(mark >> i & 1)) {
            nei.push_back(i);
        }
    }
    for (int i = 0; i < nei.size(); ++ i) {
        int t = nei[i];
        mark ^= 1 << t;
        make(t,1);
    }
    search(cur + 1);
    for (int i = 0; i < nei.size(); ++ i) {
        int t = nei[i];
        make(t,-1);
        mark ^= 1 << t;
    }
}

int work() {
    n = std::min(n,30);
    best = n;
    memset(count,0,sizeof(count));
    for (int i = 0; i < n; ++ i) {
        if (mark >> i & 1) {
            make(i,1);
        }
    }
    search(0);
    return best;
}

int main() {
    while (scanf("%d%d",&n,&m) == 2) {
        mark = 0;
        memset(graph,0,sizeof(graph));
        memset(degree,0,sizeof(degree));
        for (int i = 0; i < m; ++ i) {
            int a,b;
            scanf("%d%d",&a,&b); a --; b --;
            if (a > b) std::swap(a,b);
            if (b < 30) {
                if (!graph[a][b]) {
                    graph[a][b] = graph[b][a] = true;
                    degree[a] ++;
                    degree[b] ++;
                }
            } else {
                mark |= 1 << a;
            }
        }
        printf("%d\n",work());
    }
}
