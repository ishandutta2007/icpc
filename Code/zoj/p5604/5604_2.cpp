#include <bits/stdc++.h>

const int N = 100000 + 5;
int n,nq,W[N];
std::vector<int> edges[N];

struct FenwickTree {
    int *C,size;
    FenwickTree(int _size = 0) : size(_size) {
        C = ptr;
        ptr = C + size;
        std::fill(C,C + size,0);
    }
    void modify(int p,int dt) {
        for (int i = p; i < size; i += ~i & i + 1) C[i] += dt;
    }
    int query(int p) {
        int ret = 0;
        for (int i = std::min(p,size - 1); i >= 0; i -= ~i & i + 1) ret += C[i];
        return ret;
    }
    static int pool[40000000],*ptr;
};
int FenwickTree::pool[40000000],*FenwickTree::ptr;

struct Entry {
    int core,dis,kind,subtree;
};

std::vector<Entry> entries[N];
std::map<int,FenwickTree> bits[N][3];

int que[N],depth[N],sz[N],parent[N];
bool del[N];
int kind[N];

int bfs(int source) {
    int qe = 0;
    que[qe++] = source;
    depth[source] = 0;
    parent[source] = -1;
    for (int I = 0; I < qe; ++ I) {
        int u = que[I];
        sz[u] = 1;
        for (int v : edges[u]) {
            if (del[v] || v == parent[u]) continue;
            que[qe++] = v;
            parent[v] = u;
            depth[v] = depth[u] + 1;
        }
    }
    for (int I = qe - 1; I > 0; -- I) {
        int u = que[I];
        sz[parent[u]] += sz[u];
    }
    return qe;
}

void divide(int core) {
    int qe = bfs(core);
    for (int I = 0,best = n; I < qe; ++ I) {
        int u = que[I];
        int balance = qe - sz[u];
        for (int v : edges[u]) {
            if (del[v] || v == parent[u]) continue;
            balance = std::max(balance,sz[v]);
        }
        if (balance < best) {
            core = u;
            best = balance;
        }
    }
    bfs(core);
    kind[core] = 0;
    for (int i = 0; i < 3; ++ i) {
        bits[core][i].insert({-1,FenwickTree(depth[que[qe - 1]] + 1)});
    }
    for (int I = 0; I < qe; ++ I) {
        int u = que[I];
        int fa = parent[u];
        if (fa != -1) {
            if (kind[fa] == 0) {
                kind[u] = W[fa] == W[u] ? 0 : W[fa] < W[u] ? 1 : 2;
            } else if (kind[fa] == 1) {
                kind[u] = W[fa] <= W[u] ? 1 : -1;
            } else if (kind[fa] == 2) {
                kind[u] = W[fa] >= W[u] ? 2 : -1;
            } else {
                kind[u] = -1;
            }
        }
        if (kind[u] != -1) {
            bits[core][kind[u]][-1].modify(depth[u],1);
        }
    }
    entries[core].push_back({core,0,0,-1});
    del[core] = true;
    for (int u : edges[core]) {
        if (del[u]) continue;
        qe = bfs(u);
        for (int i = 0; i < 3; ++ i) {
            bits[core][i].insert({u,FenwickTree(depth[que[qe - 1]] + 2)});
        }
        for (int I = 0; I < qe; ++ I) {
            int v = que[I];
            if (kind[v] != -1) {
                bits[core][kind[v]][u].modify(depth[v] + 1,1);
                entries[v].push_back({core,depth[v] + 1,kind[v],u});
            }
        }
    }
    for (int u : edges[core]) {
        if (!del[u])
            divide(u);
    }
}

void prepare() {
    FenwickTree::ptr = FenwickTree::pool;
    for (int i = 0; i < n; ++ i) {
        del[i] = false;
        entries[i].clear();
        for (int j = 0; j < 3; ++ j) {
            bits[i][j].clear();
        }
    }
    divide(0);
}

int query(int x,int d) {
    int ret = 0;
    for (auto e : entries[x]) {
        for (int i = 0; i < 3; ++ i) {
            if (i == 0 || e.kind == 0 || i != e.kind) {
                ret += bits[e.core][i][-1].query(d - e.dis);
                if (e.subtree != -1) {
                    ret -= bits[e.core][i][e.subtree].query(d - e.dis);
                }
            }
        }
    }
    return ret;
}

int main() {
    int cas;
    scanf("%d",&cas);
    while (cas--) {
        scanf("%d%d",&n,&nq);
        for (int i = 0; i < n; ++ i) {
            edges[i].clear();
            scanf("%d",W + i);
        }
        for (int i = 0; i < n - 1; ++ i) {
            int a,b;
            scanf("%d%d",&a,&b); a --; b --;
            edges[a].push_back(b);
            edges[b].push_back(a);
        }
        prepare();
        while (nq--) {
            int x,d;
            scanf("%d%d",&x,&d); x --;
            printf("%d\n",query(x,d));
        }
    }
}
