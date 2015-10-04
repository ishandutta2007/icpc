#include <bits/stdc++.h>

struct BinaryIndexTree {
    int *C,size;

    bool operator < (const BinaryIndexTree &rhs) const {
        return false;
    }

    BinaryIndexTree(int n = 0) {
        size = n;
        C = bat;
        std::fill(C,C + size,0);
        bat = C + size;
    }

    void modify(int p,int dt) {
        for (int i = p; i < size; i += ~i & i + 1) C[i] += dt;
    }

    int query(int p) {
        int ret = 0;
        for (int i = std::min(p,size - 1); i >= 0; i -= ~i & i + 1) ret += C[i];
        return ret;
    }

    static int *bat;
    static int pool[40000000];
};

int *BinaryIndexTree::bat;
int BinaryIndexTree::pool[40000000];

BinaryIndexTree nill;

struct Entry : std::vector<std::pair<int,BinaryIndexTree>> {
    void done() {
        std::sort(begin(),end());
    }
    BinaryIndexTree& operator [] (int x) {
        auto it = std::lower_bound(begin(),end(),std::make_pair(x,nill));
        if (it == end() || it->first != x) return nill;
        return it->second;
    }
};

const int N = 100000 + 5;
std::vector<int> edges[N];
int n,nq,W[N];
Entry entry[N][3];
// 0 : == , 1 : < , 2 : > , -1 : bad

int sz[N],depth[N],que[N],parent[N];
bool del[N];

int bfs(int source) {
    parent[source] = -1;
    int qf = 0,qe = 0;
    que[qe++] = source;
    depth[source] = 0;
    while (qf != qe) {
        int u = que[qf++];
        sz[u] = 1;
        for (int v : edges[u]) {
            if (v == parent[u] || del[v]) continue;
            parent[v] = u;
            depth[v] = depth[u] + 1;
            que[qe++] = v;
        }
    }
    for (int I = qe - 1; I > 0; -- I) {
        int u = que[I];
        sz[parent[u]] += sz[u];
    }
    return qe;
}

const int LOG = 18;
int kind[N];
int d_parent[N];
int plca[N][LOG];
int dis[N];

int divide(int root) {
    int qe = bfs(root);
    for (int I = 0,best = n; I < qe; ++ I) {
        int u = que[I];
        int now = 0,sum = 0;
        for (int v : edges[u]) {
            if (del[v] || parent[u] == v) continue;
            now = std::max(now,sz[v]);
            sum += sz[v];
        }
        now = std::max(now,qe - sum - 1);
        if (now < best) {
            best = now;
            root = u;
        }
    }
    bfs(root);
    for (int i = 0; i < 3; ++ i) {
        entry[root][i].clear();
    }
    BinaryIndexTree tree[3];
    for (int i = 0; i < 3; ++ i) {
        tree[i] = BinaryIndexTree(depth[que[qe - 1]] + 1);
    }
    kind[root] = 0;
    for (int I = 0; I < qe; ++ I) {
        int u = que[I];
        int fa = parent[u];
        if (fa != -1) {
            d_parent[u] = root;
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
            tree[kind[u]].modify(depth[u],1);
        }
    }
    for (int i = 0; i < 3; ++ i) {
        entry[root][i].emplace_back(-1,tree[i]);
    }
    del[root] = true;
    for (int u : edges[root]) {
        if (del[u]) continue;
        if (kind[u] == -1) continue;
        qe = bfs(u);
        for (int i = 0; i < 3; ++ i) {
            tree[i] = BinaryIndexTree(depth[que[qe - 1]] + 2);
        }
        for (int I = 0; I < qe; ++ I) {
            int v = que[I];
            if (kind[v] != -1) {
                tree[kind[v]].modify(depth[v] + 1,1);
            }
        }
        for (int i = 0; i < 3; ++ i) {
            entry[root][i].emplace_back(u,tree[i]);
        }
    }
    for (int i = 0; i < 3; ++ i) {
        entry[root][i].done();
    }
    for (int v : edges[root]) {
        if (!del[v])
            divide(v);
    }
    return root;
}

int get_lca(int a,int b) {
    if (dis[a] < dis[b]) {
        std::swap(a,b);
    }
    for (int i = 0; i < LOG; ++ i) {
        if (dis[a] - dis[b] >> i & 1)
            a = plca[a][i];
    }
    if (a == b) return a;
    for (int i = LOG - 1; i >= 0; -- i) {
        if (plca[a][i] != plca[b][i]) {
            a = plca[a][i];
            b = plca[b][i];
        }
    }
    return plca[a][0];
}

int get_dis(int a,int b) {
    return dis[a] + dis[b] - 2 * dis[get_lca(a,b)];
}

int rel[N][3];

int get_rel(int a,int b) {
    int lca = get_lca(a,b);
    int c[3] = {};
    for (int i = 0; i < 3; ++ i) {
        c[i == 0 ? 0 : (i ^ 3)] += rel[a][i] - rel[lca][i];
        c[i] += rel[b][i] - rel[lca][i];
    }
    if (c[1] && c[2]) return -1;
    return c[1] ? 1 : c[2] ? 2 : 0;
}

void prepare() {
    BinaryIndexTree::bat = BinaryIndexTree::pool;
    nill = BinaryIndexTree();
    std::fill(d_parent,d_parent + n,-1);
    std::fill(del,del + n,false);
    bfs(0);
    for (int I = 0; I < n; ++ I) {
        int u = que[I];
        if (parent[u] != -1) {
            for (int i = 0; i < 3; ++ i) {
                rel[u][i] = rel[parent[u]][i];
            }
            rel[u][W[parent[u]] == W[u] ? 0 : W[parent[u]] < W[u] ? 1 : 2] ++;
        }
        dis[u] = depth[u];
        plca[u][0] = parent[u];
        for (int i = 1; i < LOG; ++ i) {
            plca[u][i] = plca[u][i - 1] == -1 ? -1 : plca[plca[u][i - 1]][i - 1];
        }
    }
    divide(0);
}

int jump(int x,int d) {
    for (int i = 0; 1 << i <= d; ++ i)
        if (d >> i & 1)
            x = plca[x][i];
    return x;
}

int move(int a,int b) {
    int lca = get_lca(a,b);
    if (lca == b) return jump(a,dis[a] - dis[b] - 1);
    return plca[b][0];
}

int query(int x,int d) {
    int ret = 0;
    for (int u = x; u != -1; u = d_parent[u]) {
        int k = get_rel(x,u);
        if (k == -1) continue;
        for (int i = 0; i < 3; ++ i) {
            if (k == 0 || i == 0 || k == i) {
                ret += entry[u][i][-1].query(d - get_dis(u,x));
                if (u != x) {
                    ret -= entry[u][i][move(x,u)].query(d - get_dis(u,x));
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
        }
        for (int i = 0; i < n; ++ i) {
            scanf("%d",W + i);
        }
        for (int i = 0; i < n - 1; ++ i) {
            int a,b;
            scanf("%d%d",&a,&b); a --; b --;
            edges[a].push_back(b);
            edges[b].push_back(a);
        }
        prepare();
        while(nq--) {
            int x,d;
            scanf("%d%d",&x,&d); x --;
            printf("%d\n",query(x,d));
        }
    }
}
