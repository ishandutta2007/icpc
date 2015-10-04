#include <stdio.h>
#include <string.h>
#include <algorithm>

const int N = 100000 + 5;
const int INF = 0x3f3f3f3f;
int X[N],Y[N];
int x0,y0,x1,y1;
int op[N],L[N],R[N],D[N];
int answer[N];
bool exist[N];
int n,m;

struct Bit {
    int C[N];

    void modify(int p,int dt) {
        for (int i = p; i < n; i += ~i & i + 1) C[i] += dt; 
    }

    int query(int p) {
        int ret = 0;
        for (int i = p; i >= 0; i -= ~i & i + 1) ret += C[i];
        return ret;
    }

    void clear() {
        std::fill(C,C + n,0);
    }
} bit;

struct SegmentTree {
#define rt get_id(l,r)
#define ls get_id(l,mid)
#define rs get_id(mid + 1,r)
    int get_id(int l,int r) {
        return l + r | l != r;
    }

    int delta[N << 1],mx[N << 1];

    void build(int A[],int l,int r) {
        delta[rt] = 0;
        if (l == r) {
            mx[rt] = exist[l] ? A[l] : -INF;
            return ;
        }
        int mid = l + r >> 1;
        build(A,l,mid);
        build(A,mid + 1,r);
        up(l,r);
    }

    void up(int l,int r) {
        int mid = l + r >> 1;
        mx[rt] = std::max(mx[ls],mx[rs]);
    }

    void make(int l,int r,int dt) {
        if (mx[rt] == -INF) return ;
        delta[rt] += dt;
        mx[rt] += dt;
    }

    void down(int l,int r) {
        int mid = l + r >> 1;
        make(l,mid,delta[rt]);
        make(mid + 1,r,delta[rt]);
        delta[rt] = 0;
    }

    void update(int L,int R,int dt,int l,int r) {
        if (L <= l && r <= R) {
            make(l,r,dt);
            return ;
        }
        down(l,r);
        int mid = l + r >> 1;
        if (L <= mid) update(L,R,dt,l,mid);
        if (mid < R)  update(L,R,dt,mid + 1,r);
        up(l,r);
    }

    void check(int limit,int l,int r) {
        if (mx[rt] <= limit) return ;
        if (l == r) {
            mx[rt] = -INF;
            if (exist[l]) {
                bit.modify(l,-1);
                exist[l] = false;
            }
            return ;
        }
        down(l,r);
        int mid = l + r >> 1;
        check(limit,l,mid);
        check(limit,mid + 1,r);
        up(l,r);
    }
} sgt[2]; 

void solve(int ox,int oy,int slop) {
    bit.clear();
    for (int i = 0; i < n; ++ i) {
        exist[i] = X[i] <= ox && Y[i] <= oy;
        if (exist[i]) {
            bit.modify(i,1);
        }
    }
    sgt[0].build(X,0,n - 1);
    sgt[1].build(Y,0,n - 1);
    for (int i = 0; i < m; ++ i) {
        if (op[i] == 1) {
            sgt[0].update(L[i],R[i],D[i],0,n - 1);
        } else if (op[i] == 2) {
            sgt[1].update(L[i],R[i],D[i],0,n - 1);
        } else {
            answer[i] += slop * (bit.query(R[i]) - bit.query(L[i] - 1));
        }
        sgt[0].check(ox,0,n - 1);
        sgt[1].check(oy,0,n - 1);
    }
}

void work() {
    std::fill(answer,answer + m,0);
    solve(x1,y1,1);
    solve(x1,y0 - 1,-1);
    solve(x0 - 1,y1,-1);
    solve(x0 - 1,y0 - 1,1);
}

int main() {
    int cas;
    scanf("%d",&cas);
    while (cas--) {
        scanf("%d",&n);
        scanf("%d%d%d%d",&x0,&y0,&x1,&y1);
        for (int i = 0; i < n; ++ i) {
            scanf("%d%d",X + i,Y + i);
        }
        scanf("%d",&m);
        for (int i = 0; i < m; ++ i) {
            scanf("%d%d%d",op + i,L + i,R + i); L[i] --; R[i] --;
            if (op[i] != 3) {
                scanf("%d",D + i);
            }
        }
        work();
        for (int i = 0; i < m; ++ i) {
            if (op[i] == 3) {
                printf("%d\n",answer[i]);
            }
        }
    }
}
