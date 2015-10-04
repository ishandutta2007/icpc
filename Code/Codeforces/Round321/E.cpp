#include <bits/stdc++.h>

typedef unsigned long long ULL;

const int N = 100000 + 5;
const ULL base = 233;
const int MOD = (int) 1e9 + 7;
ULL base_pow[N];
ULL boring[10][N];
char str[N];

struct SegmentTree {
    int get_id(int l,int r) {
        return l + r | l != r;
    }

    ULL t[N << 1];
    int tag[N << 1];

    void up(int l,int r) {
        int mid = l + r >> 1;
        t[get_id(l,r)] = (base_pow[mid - l + 1] * t[get_id(mid + 1,r)]
            + t[get_id(l,mid)]) % MOD;
    }

    void make(int l,int r,int c) {
        int id = get_id(l,r);
        t[id] = boring[c][r - l + 1];
        tag[id] = c;
    }

    void down(int l,int r) {
        if (tag[get_id(l,r)] == -1) return ;
        int mid = l + r >> 1;
        int id = get_id(l,r);
        make(l,mid,tag[id]);
        make(mid + 1,r,tag[id]);
        tag[id] = -1;
    }

    void build(int l,int r) {
        tag[get_id(l,r)] = -1;
        if (l == r) {
            t[get_id(l,r)] = str[l] - '0';
            return ;
        }
        int mid = l + r >> 1;
        build(l,mid);
        build(mid + 1,r);
        up(l,r);
    }

    void modify(int L,int R,int c,int l,int r) {
        if (L <= l && r <= R) {
            make(l,r,c);
            return ;
        }
        down(l,r);
        int mid = l + r >> 1;
        if (L <= mid) modify(L,R,c,l,mid);
        if (mid < R)  modify(L,R,c,mid + 1,r);
        up(l,r);
    }

    ULL query(int L,int R,int l,int r) {
        if (r < L || R < l) {
            return 0;
        }
        if (L <= l && r <= R) {
            return t[get_id(l,r)];
        }
        down(l,r);
        int mid = l + r >> 1;
        if (R <= mid) return query(L,R,l,mid);
        else if (mid < L) return query(L,R,mid + 1,r);
        else return (query(L,R,mid + 1,r) * base_pow[mid - std::max(L,l) + 1]
            + query(L,R,l,mid)) % MOD;
    }
} sgt;

int n,m,K;

int main() {
    base_pow[0] = 1;
    for (int i = 1; i < N; ++ i) {
        base_pow[i] = base_pow[i - 1] * base % MOD;
        for (int j = 0; j < 10; ++ j) {
            boring[j][i] = (boring[j][i - 1] * base + j) % MOD;
        }
    }
    scanf("%d%d%d",&n,&m,&K);
    scanf("%s",str);
    sgt.build(0,n - 1);
    for (int i = 0; i < m + K; ++ i) {
        int op,l,r,x;
        scanf("%d%d%d%d",&op,&l,&r,&x); l --; r --;
        if (op == 1) {
            sgt.modify(l,r,x,0,n - 1);
        } else {
            puts(sgt.query(l,r - x,0,n - 1)
                    == sgt.query(l + x,r,0,n - 1)
                    ? "YES" : "NO");
        }
    }
}
