const int N = 100000 + 5;
std::vector<int> edges[N];
int n,m;
int header[N],dfn[N],tim,parent[N],sz[N];

void get_sz(int u,int fa) {
    sz[u] = 1;
    for (int v : edges[u]) {
        if (v == fa) continue;
        get_sz(v,u);
        sz[u] += sz[v];
    }
}

void rebuild(int u,int fa,int color) {
    dfn[u] = tim ++;
    parent[u] = fa;
    header[u] = color;
    int p = -1;
    for (int v : edges[u]) {
        if (v == fa) continue;
        if (p == -1 || sz[v] > sz[p]) {
            p = v;
        }
    }
    if (p != -1) {
        rebuild(p,u,color);
    }
    for (int v : edges[u]) {
        if (v == fa || v == p) continue;
        rebuild(v,u,v);
    }
}

int get_lca(int a,int b) {
    while (header[a] != header[b]) {
        if (dfn[header[a]] < dfn[header[b]]) {
            std::swap(a,b);
        }
        a = parent[header[a]];
    }
    return dfn[a] < dfn[b] ? a : b;
}
