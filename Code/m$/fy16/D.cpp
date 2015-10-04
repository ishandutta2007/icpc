#include <bits/stdc++.h>

typedef std::vector<int> vec;
typedef std::vector<vec> mat;

const int INF = 0x3f3f3f3f;

inline void update(int &a,int b) {
    if (a > b) a = b;
}

mat mul(const mat &a,const mat &b) {
    mat ret(a.size(),vec(b[0].size(),INF));
    for (int i = 0; i < a.size(); ++ i) {
        for (int j = 0; j < a[0].size(); ++ j) {
            for (int k = 0; k < b[0].size(); ++ k) {
                update(ret[i][k],a[i][j] + b[j][k]);
            }
        }
    }
    return ret;
}

const int N = 100 + 5;
int A[N][N];
int n,m;
mat mt_pow[30];

void prepare() {
    mt_pow[0] = mat(n,vec(n,INF));
    for (int i = 0; i < n; ++ i) {
        for (int j = 0; j < n; ++ j) {
            if (i == j) continue;
            mt_pow[0][i][j] = A[i][j];
        }
    }
    for (int i = 1; i < 30; ++ i) {
        mt_pow[i] = mul(mt_pow[i - 1],mt_pow[i - 1]);
    }
}

bool check(int b) {
    mat A(1,vec(n,0));
    for (int i = 0; i < 30; ++ i) {
        if (b >> i & 1)
            A = mul(A,mt_pow[i]);
    }
    for (int i = 0; i < n; ++ i)
        if (A[0][i] <= m)
            return true;
    return false;
}

int work() {
    prepare();
    int l = 0,r = m + n;
    while (l <= r) {
        int mid = l + r >> 1;
        if (check(mid)) {
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    return l - 1;
}

int main() {
    scanf("%d%d",&n,&m);
    for (int i = 0; i < n; ++ i) {
        for (int j = 0; j < n; ++ j) {
            scanf("%d",&A[i][j]);
        }
    }
    printf("%d\n",work());
}
