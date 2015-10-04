#include <bits/stdc++.h>

const int N = 200000 + 5;
int n,A[N];
int L[N],R[N];
int answer[N];
int m;

struct Querier {
    int l,r,id;
    
    bool operator < (const Querier &rhs) const {
        return l < rhs.l;
    }
} queries[N];

int dsu[N];

int Find(int x) {
    return dsu[x] == x ? x : dsu[x] = Find(dsu[x]);
}

bool cmp(const Querier &lhs,const Querier &rhs) {
    return lhs.r < rhs.r;
}

struct Bit {
    int C[N];

    void modify(int p,int dt) {
        for (int i = p; i > 0; i -= i & -i) C[i] += dt;
    }

    int query(int p) {
        int ret = 0;
        for (int i = p; i < N; i += i & -i) ret += C[i];
        return ret;
    }
} bit;

void work() {
    std::sort(queries,queries + m);
    for (int i = 0; i <= n; ++ i) {
        dsu[i] = i;
    }
    for (int i = m - 1; i >= 0; -- i) {
        Querier &q = queries[i];
        q.r = Find(q.r);
        while (Find(A[q.r]) >= q.l) {
            dsu[q.r] = A[q.r];
            q.r = Find(q.r);
        }
    }
    std::sort(queries,queries + m,cmp);
    for (int i = 0,j = 0; i < m; ++ i) {
        Querier &q = queries[i];
        while (q.r > j) {
            int t = A[++j];
            if (t) {
                bit.modify(t,1);
            }
        }
        answer[q.id] = q.r - q.l + 1 - bit.query(q.l);
    }
}

int main() {
    freopen("data.in","r",stdin);
    freopen("data.out","w",stdout);
    scanf("%d",&n);
    std::map<int,int> map;
    for (int i = 1; i <= n; ++ i) {
        int x;
        scanf("%d",&x);
        if (map.find(x) != map.end()) {
            A[i] = map[x];
        }
        map[x] = i;
    }
    scanf("%d",&m);
    for (int i = 0; i < m; ++ i) {
        int l,r;
        scanf("%d%d",&l,&r);
        r += l - 1;
        queries[i] = {l,r,i};
    }
    work();
    for (int i = 0; i < m; ++ i) {
        printf("%d\n",answer[i]);
    }
}
