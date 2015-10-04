#include <bits/stdc++.h>

const int N = 150000 + 5;

struct Tree {
    int child[N][2];
    int n;
    int order[N],tot;
    int rm[N];
    int parent[N];
    int map[N];
    bool ban[N];
    int dfn[N],dlp;

    void dfs(int u) {
        if (u == 0) return ;
        dfs(child[u][0]);
        dfn[u] = ++ dlp;
        dfs(child[u][1]);
    }

    void prepare(int _n) {
        n = _n;
        for (int i = 1; i <= n; ++ i) {
            scanf("%d%d",child[i] + 0,child[i] + 1);
            parent[child[i][0]] = i;
            parent[child[i][1]] = i;
        }
        std::fill(dfn,dfn + n + 1,0);
        dlp = 0;
        dfs(1);
        std::fill(rm,rm + n + 1,0);
        std::fill(ban,ban + n + 1,0);
        tot = 0;
        for (int i = 1; i <= n; ++ i) {
            if (child[i][0] == 0) {
                rm[i] = -1;
            }
        }
        std::priority_queue<std::pair<int,int>> que;
        for (int i = 1; i <= n; ++ i) {
            if (rm[child[i][0]] != 0 && rm[child[i][1]] != 0) {
                que.push({dfn[i],i});
            }
        }
        while (!que.empty()) {
            int u = que.top().second; que.pop();
            rm[u] = ++ tot;
            order[tot] = u;
            int v = parent[u];
            if (v != 0 && rm[child[v][0]] && rm[child[v][1]]) {
                que.push({dfn[v],v});
            }
        }
        std::fill(map,map + n + 1,0);
    }
} tree[2];

int tr[N];
int que[N];

void construct() {
    int qf = 0,qe = 0;
    que[qe++] = 1;
    int tot = 0;
    while (qf != qe) {
        int u = que[qf++];
        tr[u] = ++ tot;
        if (tree[0].ban[u]) {
            tree[0].child[u][0] = tree[0].child[u][1] = 0;
            continue;
        }
        if (tree[0].child[u][0] != 0) {
            que[qe++] = tree[0].child[u][0];
            que[qe++] = tree[0].child[u][1];
        }
    }
    printf("%d\n",tot);
    for (int i = 0; i < qe; ++ i) {
        int u = que[i];
        printf("%d %d\n",tr[tree[0].child[u][0]],tr[tree[0].child[u][1]]);
    }
}

void work() {
    std::queue<std::pair<int,int>> que;
    int l[2] = {},r[2] = {};
    que.push({1,1});
    while (!que.empty()) {
        int a = que.front().first;
        int b = que.front().second;
        que.pop();
        if (a != 0) tree[0].map[a] = b;
        if (b != 0) tree[1].map[b] = a;

        for (int i = 0; i < 2; ++ i) {
            int aa = tree[0].child[a][i];
            int bb = tree[1].child[b][i];
            if (aa == 0 && bb == 0) {
                continue;
            }
            if (aa == 0) {
                r[1] = std::max(r[1],tree[1].rm[b]);
            }
            if (bb == 0) {
                r[0] = std::max(r[0],tree[0].rm[a]);
            }
            que.push({aa,bb});
        }
    }

    for (int d = 0; l[0] != r[0] || l[1] != r[1]; d ^= 1) {
        while (l[d] < r[d]) {
            int u = tree[d].order[++l[d]];
            int v = tree[d].map[u];
            r[d ^ 1] = std::max(r[d ^ 1],tree[d ^ 1].rm[v]);
            tree[d].ban[u] = true;
        }
    }

    construct();
}

int main() {
    freopen("lca.in","r",stdin);
    freopen("lca.out","w",stdout);
    int n;
    while (scanf("%d",&n) == 1) {
        if (n == 0) break;
        tree[0].prepare(n);
        scanf("%d",&n);
        tree[1].prepare(n);
        work();
    }
}
