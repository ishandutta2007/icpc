#pragma comment(linker, "/STACK:1024000000,1024000000")
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <vector>
typedef long long LL;

const int N = 100000 + 5;
const int MOD = (int)1e9 + 7;
int n,m;
int W[N];

inline int sqr(int x) {
    return x * 1ll * x % MOD;
}

struct SegmentTree {
    int t[N << 2];

    int query(int L,int R,int l,int r,int rt) {
        if (R < l || r < L)
            return 0;
        if (L <= l && r <= R)
            return t[rt];
        int mid = l + r >> 1;
        int ret = query(L,R,l,mid,rt << 1) + query(L,R,mid + 1,r,rt << 1 | 1);
        if (ret >= MOD)
            ret -= MOD;
        return ret;
    }

    void modify(int p,int dt,int l,int r,int rt) {
        if (l == r) {
            t[rt] = dt;
            return ;
        }
        int mid = l + r >> 1;
        if (p <= mid) modify(p,dt,l,mid,rt << 1);
        else modify(p,dt,mid + 1,r,rt << 1 | 1);
        up(rt);
    }

    void up(int rt) {
        t[rt] = t[rt << 1] + t[rt << 1 | 1];
        if (t[rt] >= MOD)
            t[rt] -= MOD;
    }

    void plus(int p,int dt,int l,int r,int rt) {
        if (l == r) {
            t[rt] += dt;
            if (t[rt] >= MOD)
                t[rt] -= MOD;
            return ;
        }
        int mid = l + r >> 1;
        if (p <= mid) plus(p,dt,l,mid,rt << 1);
        else plus(p,dt,mid + 1,r,rt << 1 | 1);
        up(rt);
    }
} tr,tr2;

std::vector<int> edges[N];
int sz[N];
int header[N],depth[N],st[N],ed[N],rd[N],tim,parent[N];
int heavy[N];

void get_sz(int u,int fa) {
    sz[u] = 1;
    for (int i = 0; i < edges[u].size(); ++ i) {
        int v = edges[u][i];
        if (v == fa) continue;
        get_sz(v,u);
        sz[u] += sz[v];
    }
}

void rebuild(int u,int fa,int col) {
    parent[u] = fa;
    st[u] = tim;
    rd[tim] = u;
    tim ++;
    header[u] = col;
    if (fa != -1) 
        depth[u] = depth[fa] + 1;
    tr2.modify(st[u],0,0,n - 1,1);
    int p = -1;
    for (int i = 0; i < edges[u].size(); ++ i) {
        int v = edges[u][i];
        if (v == fa) continue;
        if (p == -1 || sz[p] < sz[v]) 
            p = v;
    }
    heavy[u] = p;
    if (p != -1) {
        rebuild(p,u,col);
    }
    for (int i = 0; i < edges[u].size(); ++ i) {
        int v = edges[u][i];
        if (v == fa || v == p) continue;
        rebuild(v,u,v);
    }
    ed[u] = tim - 1;
    tr.modify(st[u],W[u],0,n - 1,1);
    if (col == u && fa != -1) {
        tr2.plus(st[fa],sqr(tr.query(st[u],ed[u],0,n - 1,1)),0,n - 1,1);
    }
}

void modify(int u,int w) {
    int v = u;
    while (true) {
        v = header[v];
        if (parent[v] == -1) break;
        int s = tr.query(st[v],ed[v],0,n - 1,1);
        int dt = (sqr((s + w - W[u] + MOD) % MOD) - sqr(s) + MOD) % MOD;
        tr2.plus(st[parent[v]],dt,0,n - 1,1);
        v = parent[v];
    }
    tr.modify(st[u],w,0,n - 1,1);
    W[u] = w;
}

int get_lca(int a,int b) {
    while (header[a] != header[b]) {
        if (depth[header[a]] < depth[header[b]])
            std::swap(a,b);
        a = parent[header[a]];
    }
    return depth[a] < depth[b] ? a : b;
}

inline void add(int &a,int b) {
    a += b;
    if (a >= MOD) a -= MOD;
    if (a < 0) a += MOD;
}

int calc(int a,int lca) {
    int last = -1;
    int ret = 0;
    while (true) {
        int t = heavy[a];
        if (t != last) {
            add(ret,sqr(tr.query(st[t],ed[t],0,n - 1,1)));
            if (last != -1) {
                add(ret,-sqr(tr.query(st[last],ed[last],0,n - 1,1)));
            }
        }
        int v = header[a];
        if (depth[v] <= depth[lca]) {
            v = lca;
        }
        add(ret,tr2.query(st[v],st[a],0,n - 1,1));
        if (v == lca) {
            break;
        }
        last = v;
        a = parent[v];
    }
    return ret;
}

int query(int a,int b) {
    int lca = get_lca(a,b);
    int ret = sqr(tr.query(0,n - 1,0,n - 1,1));
    add(ret,-sqr(tr.query(0,n - 1,0,n - 1,1) - tr.query(st[lca],ed[lca],0,n - 1,1)));
    add(ret,-calc(a,lca));
    add(ret,-calc(b,lca));
    add(ret,calc(lca,lca));
    return ret;
}

int main() {
    while (scanf("%d%d",&n,&m) == 2) {
        for (int i = 0; i < n; ++ i) {
            scanf("%d",W + i);
        }
        for (int i = 0; i < n; ++ i) {
            edges[i].clear();
        }
        for (int i = 0; i < n - 1; ++ i) {
            int a,b;
            scanf("%d%d",&a,&b); a --; b --;
            edges[a].push_back(b);
            edges[b].push_back(a);
        }
        get_sz(0,-1);
        tim = 0;
        rebuild(0,-1,0);
        while (m --) {
            int op,a,b;
            scanf("%d%d%d",&op,&a,&b);
            if (op == 1) {
                a --;
                modify(a,b);
            } else {
                a --; b --;
                printf("%d\n",query(a,b));
            }
        }
    }
}
