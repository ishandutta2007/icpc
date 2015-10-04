#include <bits/stdc++.h>

const int N = 200000 + 5;
int n;
std::vector<int> edges[N];
int que[N],qf,qe;
int parent[N];
bool mark[N];
int diameter[N],tot;
int dis[N];
int A[N];

int pa,pb;

void bfs(int source) {
    qf = 0,qe = 0;
    que[qe++] = source;
    parent[source] = -1;
    dis[source] = 0;
    while (qf != qe) {
        int u = que[qf++];
        for (int v : edges[u]) {
            if (v == parent[u]) continue;
            if (mark[v]) continue;
            parent[v] = u;
            que[qe++] = v;
            dis[v] = dis[u] + 1;
        }
    }
}

std::vector<int> vl[N];

bool solve(int limit) {
    pa = pb = -1;
    for (int i = 0; i < tot; ++ i) {
        vl[i].clear();
    }
    for (int i = 0; i < tot; ++ i) {
        int d = limit - A[i];
        if (d < 0) return false;
        vl[std::min(i + d,tot - 1)].push_back(std::max(0,i - d));
    }
    for (int i = 0; i < tot; ++ i) {
        if (vl[i].empty()) continue;
        bool flag = true;
        for (int l : vl[i]) {
            if (pa < l && pb < l) {
                flag = false;
                break;
            }
        }
        if (!flag) {
            if (pa == -1) {
                pa = i;
            } else if (pb == -1) {
                pb = i;
            } else {
                return false;
            }
        }
    }
    if (pb == -1) {
        pb = pa == 0 ? 1 : 0;
    }
    return true;
}

void work() {
    std::fill(mark,mark + n,false);
    bfs(0);
    bfs(que[n - 1]);
    tot = 0;
    for (int u = que[n - 1]; u != -1; u = parent[u]) {
        diameter[tot++] = u;
        mark[u] = true;
    }
    for (int i = 0; i < tot; ++ i) {
        int u = diameter[i];
        bfs(u);
        A[i] = dis[que[qe - 1]];
    }
    int l = 0,r = n;
    while (l <= r) {
        int mid = l + r >> 1;
        if (solve(mid)) {
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    solve(r + 1);
    printf("%d %d %d\n",r + 1,diameter[pa] + 1,diameter[pb] + 1);
}

int main() {
    int cas;
    scanf("%d",&cas);
    while (cas--) {
        scanf("%d",&n);
        for (int i = 0; i < n; ++ i) {
            edges[i].clear();
        }
        for (int i = 0; i < n - 1; ++ i) {
            int a,b;
            scanf("%d%d",&a,&b); a --; b --;
            edges[a].push_back(b);
            edges[b].push_back(a);
        }
        work();
    }
}
