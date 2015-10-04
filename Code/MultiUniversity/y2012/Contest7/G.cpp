#pragma comment(linker, "/STACK:1024000000,1024000000")
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <vector>
#include <set>

const int N = 50000 + 5;
int pr[1000000 + 1];
int A[N],B[N];
int answer[N];
int n,m;
std::set<std::pair<int,int> > set[N];
std::set<std::pair<int,int> >::iterator it,it2;
int idx[N];
std::vector<int> edges[N];

void insert(int id,int a,int b) {
    it2 = set[id].upper_bound({a,b});
    bool bad = false;
    if (it2 != set[id].end() && it2->second > b)
        bad = true;
    if (it2 != set[id].begin()) {
        -- it2;
        while (true) {
            if (it2->second <= b) {
                if (it2 == set[id].begin()) {
                    set[id].erase(it2);
                    break;
                } else {
                    set[id].erase(it2 --);
                }
            } else {
                break;
            }
        }
    }
    if (!bad)
        set[id].insert({a,b});
}

int merge(int a,int b) {
    if (set[a].size() < set[b].size())
        std::swap(a,b);
    for (it = set[b].begin(); it != set[b].end(); ++ it) {
        insert(a,it->first,it->second);
    }
    return a;
}

void dfs(int u) {
    idx[u] = u;
    set[u].clear();
    answer[u] = -1;
    for (int i = 0; i < edges[u].size(); ++ i) {
        int v = edges[u][i];
        dfs(v);
        idx[u] = merge(idx[u],idx[v]);
    }
    it = set[idx[u]].upper_bound({A[u],1000000});
    if (it != set[idx[u]].end()) {
        answer[u] = pr[it->second];
    }
    insert(idx[u],A[u],B[u]);
}

int main() {
    int cas;
    scanf("%d",&cas);
    while (cas--) {
        scanf("%d%d",&n,&m);
        for (int i = 0; i < n; ++ i) {
            edges[i].clear();
        }
        for (int i = 1; i < n; ++ i) {
            int a,b,c;
            scanf("%d%d%d",&a,&b,&c);
            edges[a].push_back(i);
            A[i] = c;
            B[i] = b;
            pr[b] = i;
        }
        dfs(0);
        while (m--) {
            int x;
            scanf("%d",&x);
            printf("%d\n",answer[x]);
        }
    }
}

