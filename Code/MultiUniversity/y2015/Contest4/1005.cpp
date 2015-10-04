#include <bits/stdc++.h>

const int N = 100000 + 5;
int A[N];
int answer[N];
int n;
int st[N],rd[N],dll,ed[N],depth[N],sz[N],header[N],parent[N];
std::vector<int> edges[N];

void get_sz(int u) {
    sz[u] = 1;
    for (int v : edges[u]) {
        get_sz(v);
        sz[u] += sz[v];
    }
}

void rebuild(int u,int col) {
    rd[dll] = u;
    st[u] = dll ++;
    header[u] = col;
    int p = -1;
    for (int v : edges[u]) {
        parent[v] = u;
        if (p == -1 || sz[p] < sz[v])
            p = v;
    }
    if (p != -1) {
        rebuild(p,col);
    }
    for (int v : edges[u]) {
        if (v != p) {
            rebuild(v,v);
        }
    }
    ed[u] = dll - 1;
}

struct Node {
    int val,sz;
    bool rev_tag;
};

struct SegmentTree {
    Node t[N << 2];

    void build(int l,int r,int rt) {
        t[rt] = {0,0,false};
        if (l == r) return ;
        int mid = l + r >> 1;
        build(l,mid,rt << 1);
        build(mid + 1,r,rt << 1 | 1);
    }

    Node merge(const Node &a,const Node &b) {
        if (b.sz == 0) return a;
        else if (a.sz == 0) return b;
        return {a.val == b.val ? a.val : -1,a.sz + b.sz,false};
    }

    void down(int rt) {
        if (!t[rt].rev_tag) return ;
        t[rt << 1].rev_tag ^= 1;
        if (t[rt << 1].val != -1) {
            t[rt << 1].val ^= 1;
        }
        t[rt << 1 | 1].rev_tag ^= 1;
        if (t[rt << 1 | 1].val != -1) {
            t[rt << 1 | 1].val ^= 1;
        }
        t[rt].rev_tag = false;
    }

    void update(int p,int v,int l,int r,int rt) {
        if (l == r) {
            t[rt] = {v,1,false};
            return ;
        }
        down(rt);
        int mid = l + r >> 1;
        if (p <= mid) update(p,v,l,mid,rt << 1);
        else update(p,v,mid + 1,r,rt << 1 | 1);
        t[rt] = merge(t[rt << 1],t[rt << 1 | 1]);
    }

    int query(int L,int R,int l,int r,int rt) {

    }
};

void work() {
    for (int i = 1; i < n; ++ i) {
        edges[A[i]].push_back(i);
    }
    get_sz(0);
    dll = 0;
    rebuild(0,0);
}

int main() {
    while (scanf("%d",&n) == 1) {
        for (int i = 1; i < n; ++ i) {
            scanf("%d",A + i);
        }
        work();
        for (int i = 1; i < n; ++ i) {
            printf("%d\n",answer[i]);
        }
    }
}
