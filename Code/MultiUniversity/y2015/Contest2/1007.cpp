#include <bits/stdc++.h>
typedef long long LL;

struct Node {
    int uncover;
    int tag;
    LL sum;
    int max_tag;

    Node() {}
    Node(int uncover,int tag,LL sum,int max_tag) : uncover(uncover),tag(tag),sum(sum),max_tag(max_tag) {}

    Node operator + (const Node &rhs) const {
        return Node(uncover + rhs.uncover,-1,sum + rhs.sum,std::max(max_tag,rhs.max_tag));
    }

    Node operator + (int tg) {
        if (tg == -1) return *this;
        return Node(0,tg,sum + uncover * 1ll * tg,uncover != 0 ? tg : max_tag);
    }
};

const int N = 1000000 + 5;
int n,A[N],m;

struct SegmentTree {
#define ls get_id(l,mid)
#define rs get_id(mid + 1,r)
#define rt get_id(l,r)
    int get_id(int l,int r) {
        return l + r | l != r;
    }

    Node t[N << 1];

    void build(int l,int r) {
        if (l == r) {
            t[rt] = Node(0,A[l],A[l],A[l]);
            return ;
        }
        int mid = l + r >> 1;
        build(l,mid);
        build(mid + 1,r);
        t[rt] = t[ls] + t[rs];
    }

    void clear(int tg,int l,int r) {
        if (t[rt].max_tag <= tg) {
            return ;
        }
        if (l == r) {
            t[rt] = Node(1,-1,0,-1);
            return ;
        }
        int mid = l + r >> 1;
        clear(tg,l,mid);
        clear(tg,mid + 1,r);
        t[rt] = t[ls] + t[rs];
    }

    void update(int L,int R,int tg,int l,int r) {
        if (r < L || R < l || t[rt].tag != -1 && t[rt].tag <= tg) {
            return ;
        }
        if (L <= l && r <= R) {
            clear(tg,l,r);
            t[rt] = t[rt] + tg;
            return ;
        }
        int mid = l + r >> 1;
        update(L,R,tg,l,mid);
        update(L,R,tg,mid + 1,r);
        t[rt] = t[ls] + t[rs] + t[rt].tag;
    }

    Node query(int L,int R,int l,int r) {
        if (L <= l && r <= R) {
            return t[rt];
        }
        int mid = l + r >> 1;
        if (L <= mid && mid < R) return query(L,R,l,mid) + query(L,R,mid + 1,r) + t[rt].tag;
        else if (L <= mid) return query(L,R,l,mid) + t[rt].tag;
        else return query(L,R,mid + 1,r) + t[rt].tag;
    }
} sgt;

inline void read(int &x) {
    char c;
    for (c = getchar(); c < '0' || c > '9'; c = getchar());
    for (x = 0; c >= '0' && c <= '9'; c = getchar()) x = x * 10 + c - '0';
}

template<typename T>
inline void print(T x) {
    if (x == 0) {
        putchar('0');
    } else {
        static int A[66];
        int tot = 0;
        while (x) {
            A[tot++] = x - x / 10 * 10;
            x /= 10;
        }
        for (int i = tot - 1; i >= 0; -- i) {
            putchar(A[i] + '0');
        }
    }
    puts("");
}

int main() {
    //freopen("1007_std.in","r",stdin);
    //freopen("1007.out","w",stdout);
    int cas;
    read(cas);
    while (cas--) {
        read(n),read(m);
        for (int i = 0; i < n; ++ i) {
            read(A[i]);
        }
        sgt.build(0,n - 1);
        for (int i = 0; i < m; ++ i) {
            int op,x,y,t;
            read(op);
            read(x);
            read(y);
            x --; y --;
            if (op == 0) {
                read(t);
                sgt.update(x,y,t,0,n - 1);
            } else if (op == 1) {
                print(sgt.query(x,y,0,n - 1).max_tag);
            } else {
                print(sgt.query(x,y,0,n - 1).sum);
            }
        }
    }
    //fprintf(stderr,"%.10f\n",clock() * 1. / CLOCKS_PER_SEC);
}
