#include <bits/stdc++.h>

const int INF = 0x3f3f3f3f;
const int N = 100000 + 5;
int A[N],B[N],n;
int answer[N];

struct SegmentTree {
    void build(int l,int r,int rt) {
        if (l == r) {
            t[rt] = A[l];
            return ;
        }
        int mid = l + r >> 1;
        build(l,mid,rt << 1);
        build(mid + 1,r,rt << 1 | 1);
        up(rt);
    }

    void up(int rt) {
        t[rt] = std::max(t[rt << 1],t[rt << 1 | 1]);
    }

    int query(int L,int R,int l,int r,int rt) {
        if (R < l || r < L) {
            return 0;
        }
        if (L <= l && r <= R) {
            return t[rt];
        }
        int mid = l + r >> 1;
        return std::max(query(L,R,l,mid,rt << 1),
                query(L,R,mid + 1,r,rt << 1 | 1));
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

    int t[N << 2];
} sgt;

void work() {
    A[0] = 0;
    A[n + 1] = 0;
    sgt.build(0,n + 1,1);
    std::set<int> set;
    set.insert(0);
    for (int i = 1; i <= n; ++ i) {
        int t = *--set.upper_bound(B[i]);
        if (t == B[i]) continue;
        int x = B[sgt.query(t + 1,B[i] + 1,0,n + 1,1)];

        if (x != B[i] + 1) {
            for (int j = x; j <= B[i]; ++ j) {
                set.insert(j);
                sgt.modify(j,0,0,n + 1,1);
            }
            for (int j = x + 1; j <= B[i]; ++ j) {
                answer[A[j - 1]] = A[j];
            }
            answer[i] = A[x];
        } else {
            sgt.modify(B[i] + 1,0,0,n + 1,1);
        }
    }
    for (int i = 1; i <= n; ++ i) {
        if (i > 1) putchar(' ');
        printf("%d",answer[i]);
    }
    puts("");
}

inline void read(int &x) {
    char c;
    for (c = getchar(); c < '0' || c > '9'; c = getchar());
    for (x = 0; c >= '0' && c <= '9'; c = getchar()) x = x * 10 + c - '0';
}

int main() {
    int cas;
    read(cas);
    while (cas--) {
        read(n);
        for (int i = 1; i <= n; ++ i) {
            read(A[i]);
            B[A[i]] = i;
        }
        work();
    }
}
