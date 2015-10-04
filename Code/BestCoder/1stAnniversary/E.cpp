#include <bits/stdc++.h>
using LL = long long ;

const int N = 100000 + 5;
int n,m;
std::vector<int> edges[N];
int W[N];
LL answer;

int que[N];
int parent[N];
bool used[N];
int sz[N],balance[N];

int bfs(int source,int fa = -1) {
    int qf = 0,qe = 0;
    que[qe++] = source;
    parent[source] = fa;
    while (qf != qe) {
        int u = que[qf++];
        sz[u] = 1;
        balance[u] = 0;
        for (int v : edges[u]) {
            if (used[v] || parent[u] == v) continue;
            que[qe++] = v;
            parent[v] = u;
        }
    }
    return qe;
}

struct San : std::vector<int> {
    void dispose() {
        std::sort(begin(),end());
        erase(std::unique(begin(),end()),end());
    }

    int get(int x) {
        return std::lower_bound(begin(),end(),x) - begin();
    }
} ss;

int L[N],R[N];

struct Bit {
    int C[N];

    void modify(int p,int dt) {
        for (int i = p; i < N; i += ~i & i + 1) C[i] += dt;
    }

    int query(int p) {
        int ret = 0;
        for (int i = p; i >= 0; i -= ~i & i + 1) ret += C[i];
        return ret;
    }
} bit;

LL calc(int source,int fa = -1) {
    int qf = 0,qe = 0;
    que[qe++] = source;
    parent[source] = fa;
    L[source] = R[source] = W[source];
    if (fa != -1) {
        L[source] = std::min(L[source],W[fa]);
        R[source] = std::max(R[source],W[fa]);
    }
    std::vector<std::pair<int,int>> A,B;
    while (qf != qe) {
        int u = que[qf++];
        if (ss[R[u]] - ss[L[u]] > m) continue;
        A.push_back({L[u],R[u]});
        if (ss[R[u]] - m <= ss[L[u]] + m) {
            B.push_back({R[u],L[u]});
        }
        for (int v : edges[u]) {
            if (!used[v] && v != parent[u]) {
                L[v] = std::min(W[v],L[u]);
                R[v] = std::max(W[v],R[u]);
                parent[v] = u;
                que[qe++] = v;
            }
        }
    }
    std::sort(A.begin(),A.end());
    std::sort(B.begin(),B.end());
    int i,j;
    LL ret = 0;
    for (i = (int)B.size() - 1,j = (int)A.size() - 1; i >= 0; -- i) {
        while (j >= 0 && ss[A[j].first] >= ss[B[i].first] - m) {
            bit.modify(A[j].second,1);
            -- j;
        }
        ret += bit.query(ss.get(ss[B[i].second] + m + 1) - 1);
    }
    for (i = j + 1; i < A.size(); ++ i) {
            bit.modify(A[i].second,-1);
    }
    return ret;
}

void divide(int root) {
    int tot = bfs(root);
    root = que[tot - 1];
    for (int I = tot - 1; I >= 0; -- I) {
        int u = que[I];
        if (I) {
            balance[parent[u]] = std::max(balance[parent[u]],sz[u]);
            sz[parent[u]] += sz[u];
        }
        balance[u] = std::max(balance[u],tot - sz[u]);
        if (balance[u] < balance[root]) {
            root = u;
        }
    }

    for (int u : edges[root]) {
        if (!used[u]) {
            answer -= calc(u,root);
        }
    }

    answer += calc(root);

    used[root] = true;

    for (int u : edges[root]) {
        if (!used[u]) {
            divide(u);
        }
    }

}

LL work() {
    answer = 0;
    std::fill(used,used + n,false);
    ss.clear();
    for (int i = 0; i < n; ++ i) {
        ss.push_back(W[i]);
    }
    ss.dispose();
    for (int i = 0; i < n; ++ i) {
        W[i] = ss.get(W[i]);
    }
    divide(0);
    return answer - n;
}

int main() {
    int cas;
    scanf("%d",&cas);
    while (cas--) {
        scanf("%d%d",&n,&m);
        for (int i = 0; i < n; ++ i) {
            scanf("%d",W + i);
            edges[i].clear();
        }
        for (int i = 0; i < n - 1; ++ i) {
            int a,b;
            scanf("%d%d",&a,&b); a --; b --;
            edges[a].push_back(b);
            edges[b].push_back(a);
        }
        printf("%I64d\n",work());
    }
}
