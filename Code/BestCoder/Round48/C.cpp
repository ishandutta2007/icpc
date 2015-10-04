#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <map>
#include <vector>

const int N = 50000 + 5;
const int MOD = (int) 1e9 + 7;
const int inv2 = MOD + 1 >> 1;
const int BLOCK = 400 + 5;
int n,m;
int A[N],B[N];
int tot;
std::map<int,int> map;
std::vector<int> C[N];
int block[N / BLOCK][N],pw[N / BLOCK][N],btot;

struct Node {
    Node *lc,*rc;
    int val;
} *tree[N],pool[N * 400],*bat,*nill;

inline void add(int &a,int b) {
    a += b;
    if (a >= MOD) a -= MOD;
    if (a < 0) a += MOD;
}

void init() {
    bat = pool;
    nill = bat ++;
    nill->lc = nill->rc = nill;
    nill->val = 0;
    tree[0] = nill;
}

std::vector<std::pair<int,int>> lights[N];

void insert(Node *a,Node *&b,int p,int dt,int l,int r) {
    b = bat ++;
    *b = *a;
    add(b->val,dt);
    if (l == r) {
        return ;
    }
    int mid = l + r >> 1;
    if (p <= mid) insert(a->lc,b->lc,p,dt,l,mid);
    else insert(a->rc,b->rc,p,dt,mid + 1,r);
}

int query(Node *u,int L,int R,int l,int r) {
    if (L <= l && r <= R) {
        return u->val;
    }
    int mid = l + r >> 1;
    int ret = 0;
    if (L <= mid) add(ret,query(u->lc,L,R,l,mid));
    if (mid < R)  add(ret,query(u->rc,L,R,mid + 1,r));
    return ret;
}

void prepare() {
    map.clear();
    tot = 0;
    for (int i = 1; i <= n; ++ i) {
        if (map.find(A[i]) == map.end()) {
            map[A[i]] = tot;
            B[tot] = A[i];
            C[tot].clear();
            tot ++;
        }
        C[map[A[i]]].push_back(i);
    }
    for (int i = 0; i <= n; ++ i) {
        lights[i].clear();
    }
    btot = 0;
    for (int i = 0; i < tot; ++ i) {
        if (C[i].size() > BLOCK) {
            for (int j = 1; j <= n; ++ j) {
                block[btot][j] = 0;
            }
            for (int j = 0; j < C[i].size(); ++ j) {
                block[btot][C[i][j]] ++;
            }
            for (int j = 1; j <= n; ++ j) {
                block[btot][j] += block[btot][j - 1];
            }
            pw[btot][0] = 1;
            for (int j = 1; j <= C[i].size(); ++ j) {
                pw[btot][j] = pw[btot][j - 1] * 1ll * B[i] % MOD;
            }
            btot ++;
        } else {
            for (int j = 0; j < C[i].size(); ++ j) {
                int tmp = B[i],tmp2 = 0;
                for (int k = j; k >= 0; -- k) {
                    lights[C[i][j]].push_back({C[i][k],tmp - tmp2});
                    if (j + 1 < C[i].size()) {
                        lights[C[i][j + 1]].push_back({C[i][k],tmp2 - tmp});
                    }
                    tmp2 = tmp;
                    tmp = tmp * 1ll * B[i] % MOD;
                }
            }
        }
    }
    init();
    for (int i = 1; i <= n; ++ i) {
        Node *now = tree[i - 1];
        for (auto t : lights[i]) {
            Node *after = NULL;
            insert(now,after,t.first,t.second,1,n);
            now = after;
        }
        tree[i] = now;
    }
}

int work(int l,int r) {
    int ret = query(tree[r],l,n,1,n);
    for (int i = 0; i < btot; ++ i) {
        int cnt = block[i][r] - block[i][l - 1];
        add(ret,pw[i][cnt]);
    }
    return ret;
}

int main() {
    int cas;
    scanf("%d",&cas);
    while (cas--) {
        scanf("%d%d",&n,&m);
        for (int i = 1; i <= n; ++ i) {
            scanf("%d",A + i);
        }
        prepare();
        int last = 0;
        while (m -- ) {
            int l,r;
            scanf("%d%d",&l,&r);
            l = (l ^ last) % n + 1;
            r = (r ^ last) % n + 1;
            if (l > r) {
                std::swap(l,r);
            }
            last = work(l,r);
            printf("%d\n",last);
        }
    }
}
