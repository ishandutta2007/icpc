#include <bits/stdc++.h>

const int N = 100000 + 5;
int n;
std::vector<int> edges[N];
bool vis[N];
int root;
int parent[N];
bool in_cycle[N];
int cycle[N],tot;
int sz[N];
int last[N];
bool bad[N];
bool ok[N];
std::vector<int> que[N];

void my_assert(bool flag) {
    if (!flag) {
        printf("%d\n",1 / 0);
    }
}

bool solve(int size) {
    std::fill(last,last + size,0);
    std::fill(bad,bad + size,false);
    std::fill(sz,sz + n,1);
    int sum = 0;
    for (int i = 0; i < tot; ++ i) {
        int source = cycle[i];
        for (int I = (int)que[i].size() - 1; I >= 1; -- I) {
            int u = que[i][I];
            if (sz[u] > size) {
                return false;
            } else if (sz[u] == size) {
                sz[u] = 0;
            } else {
                sz[parent[u]] += sz[u];
            }
        }
        if (sz[source] > size) {
            return false;
        }
        sum += sz[source];
        if (sum - last[sum % size] > size) {
            bad[sum % size] = true;
        }
        last[sum % size] = sum;
    }
    for (int i = 0; i < size; ++ i) {
        if (!bad[i] && sum - last[i] <= size) {
            return true;
        }
    }
    return false;
}

int work() {
    {
        std::fill(vis,vis + n,false);
        std::queue<int> que;
        que.push(0);
        vis[0] = true;
        parent[0] = -1;
        bool flag = false;
        while (!que.empty() && !flag) {
            int u = que.front(); que.pop();
            for (int v : edges[u]) {
                if (parent[u] == v) continue;
                if (vis[v]) {
                    root = v;
                    flag = true;
                    break;
                }
                parent[v] = u;
                vis[v] = true;
                que.push(v);
            }
        }
    }
    {
        std::fill(vis,vis + n,false);
        std::fill(in_cycle,in_cycle + n,false);
        std::queue<int> que;
        que.push(root);
        parent[root] = -1;
        vis[root] = true;
        bool flag = false;
        while (!que.empty() && !flag) {
            int u = que.front(); que.pop();
            for (int v : edges[u]) {
                if (parent[u] == v) continue;
                if (vis[v]) {
                    tot = 0;
                    while (v != -1) {
                        in_cycle[v] = true;
                        cycle[tot++] = v;
                        v = parent[v];
                    }
                    int tmp = tot;
                    while (u != root) {
                        in_cycle[u] = true;
                        cycle[tot++] = u;
                        u = parent[u];
                    }
                    std::reverse(cycle + tmp,cycle + tot);
                    flag = true;
                    break;
                }
                vis[v] = true;
                parent[v] = u;
                que.push(v);
            }
        }
    }
    {
        for (int i = 0; i < tot; ++ i) {
            int source = cycle[i];
            int qf = 0;
            parent[source] = -1;
            que[i].clear();
            que[i].push_back(source);
            while (qf != que[i].size()) {
                int u = que[i][qf++];
                sz[u] = 1;
                for (int v : edges[u]) {
                    if (v == parent[u] || in_cycle[v]) continue;
                    que[i].push_back(v);
                    parent[v] = u;
                }
            }
        }
    }
    int ret = 1;
    for (int size = 2; size <= n; ++ size) {
        if (n % size == 0) {
            ret += solve(size);
        }
    }
    return ret;
}

int main() {
    //freopen("1003_std.in","r",stdin);
    //freopen("1003.out","w",stdout);
    while (scanf("%d",&n) == 1) {
        for (int i = 0; i < n; ++ i) {
            edges[i].clear();
        }
        for (int i = 0; i < n; ++ i) {
            int x;
            scanf("%d",&x); x --;
            edges[i].push_back(x);
            edges[x].push_back(i);
        }
        printf("%d\n",work());
    }
    //fprintf(stderr,"%.10f\n",(double)clock() / CLOCKS_PER_SEC);
}
