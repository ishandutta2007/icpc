const int kN = 100000 + 5;
std::vector<int> edges[kN];
int n;
bool vis[kN];
int parent[kN];
int sz[kN];
int que[kN];
int balance[kN];

int bfs(int source,int fa = -1) {
    int qf = 0,qe = 0;
    que[qe++] = source;
    parent[source] = fa;
    while (qf != qe) {
        int u = que[qf++];
        sz[u] = 1;
        balance[u] = 0;
        for (int v : edges[u]) {
            if (!vis[v] && parent[u] != v) {
                parent[v] = u;
                que[qe++] = v;
            }
        }
    }
    for (int i = qe - 1; i >= 0; -- i) {
        int u = que[i];
        if (i) {
            sz[parent[u]] += sz[u];
            balance[parent[u]] = std::max(balance[parent[u]],sz[u]);
        }
        balance[u] = std::max(balance[u],qe - sz[u]);
    }
    return qe;
}

void divide(int root) {
    int tot = bfs(root);
    for (int i = tot - 1; i > 0; -- i) {
        int u = que[i];
        if (balance[u] < balance[root]) {
            root = u;
        }
    }
    bfs(root);

    // balabalah

    vis[root] = true;
    for (int u : edges[root]) {
        if (!vis[u]) {
            divide(u);
        }
    }
}
