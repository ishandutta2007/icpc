#include <bits/stdc++.h>

bool doge[10000000 + 1];
int prime[700000 + 5],ptot;

void get_prime(int n) {
    for (int i = 2; i <= n; ++ i) {
        if (!doge[i]) {
            prime[ptot++] = i;
        }
        for (int j = 0; j < ptot; ++ j) {
            if (i * prime[j] > n) break;
            doge[i * prime[j]] = true;
            if (i % prime[j] == 0) break;
        }
    }
}

void init() {
    get_prime(10000000);
    doge[1] = true;
    for (int x = 1; x <= 10000000; x <<= 1) {
        doge[x] = false;
    }
    doge[6] = false;
    doge[0] = false;
}

const int N = 100000 + 5;
int n,A[N];
int m;

struct SegmentTree {
#define ls get_id(l,mid)
#define rs get_id(mid + 1,r)
#define rt get_id(l,r)
    int get_id(int l,int r) {
        return l + r | l != r;
    }

    int t[N << 1];
    int sum[N << 1];

    void build(int l,int r) {
        if (l == r) {
            t[rt] = A[l];
            sum[rt] = doge[A[l]] == false;
            return ;
        }
        int mid = l + r >> 1;
        build(l,mid);
        build(mid + 1,r);
        up(l,r);
    }

    void up(int l,int r) {
        int mid = l + r >> 1;
        t[rt] = std::max(t[ls],t[rs]);
        sum[rt] = sum[ls] + sum[rs];
    }

    void update(int L,int R,int v,int l,int r) {
        if (R < l || r < L || t[rt] < v) {
            return ;
        }
        if (l == r) {
            t[rt] = t[rt] % v;
            sum[rt] = doge[t[rt]] == false;
            return ;
        }

        int mid = l + r >> 1;
        update(L,R,v,l,mid);
        update(L,R,v,mid + 1,r);
        up(l,r);
    }

    void modify(int p,int v,int l,int r) {
        if (l == r) {
            t[rt] = v;
            sum[rt] = doge[v] == false;
            return ;
        }
        int mid = l + r >> 1;
        if (p <= mid) modify(p,v,l,mid);
        else modify(p,v,mid + 1,r);
        up(l,r);
    }

    int query(int L,int R,int l,int r) {
        if (L <= l && r <= R) {
            return sum[rt];
        }
        int mid = l + r >> 1;
        int ret = 0;
        if (L <= mid) ret += query(L,R,l,mid);
        if (mid < R)  ret += query(L,R,mid + 1,r);
        return ret;
    }
} sgt;

int main() {
    init();
    while (scanf("%d",&n) == 1) {
        for (int i = 0; i < n; ++ i) {
            scanf("%d",A + i);
        }
        sgt.build(0,n - 1);
        scanf("%d",&m);
        while (m--) {
            int op,l,r,x;
            scanf("%d%d%d",&op,&l,&r);
            if (op == 1) {
                l --; r --;
                printf("%d\n",sgt.query(l,r,0,n - 1));
            } else if (op == 2) {
                scanf("%d",&x);
                l --; r --;
                sgt.update(l,r,x,0,n - 1);
            } else {
                l --;
                sgt.modify(l,r,0,n - 1);
            }
        }
    }
}
