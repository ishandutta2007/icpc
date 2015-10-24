#include <bits/stdc++.h>
typedef long long LL;

const int MOD = (int)1e9 + 9;
int n,c;
LL m;

using vec = std::vector<int>;
using mat = std::vector<vec>;

inline void add(int &a,int b) {
    a += b;
    if (a >= MOD) a -= MOD;
}

mat mul(const mat &A,const mat &B) {
    mat ret(A.size(),vec(B[0].size()));
    for (int i = 0; i < A.size(); ++ i)
        for (int j = 0; j < A[0].size(); ++ j)
            for (int k = 0; k < B[i].size(); ++ k)
                add(ret[i][k],A[i][j] * 1ll * B[j][k] % MOD);
    return ret;
}

int A[20];

int main() {
    scanf("%d%I64d%d",&n,&m,&c);
    for (int i = 0; i < n; ++ i) {
        scanf("%d",A + i);
    }
    if (m <= n) {
        printf("%d\n",A[m - 1]);
        return 0;
    }
    m -= n;
    mat L(1,vec(n));
    for (int i = 0; i < n; ++ i)
        L[0][i] = A[i];
    mat R(n,vec(n));
    for (int i = 0; i + 1 < n; ++ i)
        R[i + 1][i] = 1;
    for (int i = 0; i < c; ++ i) {
        int x;
        scanf("%d",&x);
        R[n - 1 - x + 1][n - 1] = 1;
    }
    while (m) {
        if (m & 1) L = mul(L,R);
        R = mul(R,R);
        m >>= 1;
    }
    printf("%d\n",L[0][n - 1]);
}
