#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <vector>

const int N = 100 + 1;
int MOD;

inline void add(int &a,int b) {
    a += b;
    if (a >= MOD) a -= MOD;
}

int det(int A[N][N],int n) {
    int ret = 1;
    for (int i = 0; i < n; ++ i) {
        if (A[i][i] == 0) {
            for (int j = i + 1; j < n; ++ j) {
                if (A[j][i]) {
                    for (int k = i; k < n; ++ k) {
                        std::swap(A[i][k],A[j][k]);
                    }
                    ret = -ret;
                    break;
                }
            }
            if (A[i][i] == 0) return 0;
        }
        for (int j = i + 1; j < n; ++ j) {
            int a = 1 % MOD,b = 0,c = 0,d = 1 % MOD;
            int x = A[i][i],y = A[j][i];
            while (y) {
                int t = x / y;
                if (t < 0) t += MOD;
                add(a,MOD - c * 1ll * t % MOD);
                add(b,MOD - d * 1ll * t % MOD);
                std::swap(a,c);
                std::swap(b,d);
                x %= y;
                std::swap(x,y);
                ret = -ret;
            }
            for (int k = 0; k < n; ++ k) {
                int q = A[i][k],w = A[j][k];
                A[i][k] = (a * 1ll * q + b * 1ll * w) % MOD;
                A[j][k] = (c * 1ll * q + d * 1ll * w) % MOD;
            }
        }
        ret = A[i][i] * 1ll * ret % MOD;
    }
    if (ret < 0) {
        ret += MOD;
    }
    return ret % MOD;
}

int n,m,q;
int A[N][N];

typedef std::vector<int> vec;
typedef std::vector<vec> mat;

mat mul(const mat &A,const mat &B) {
    mat ret(A.size(),vec(B[0].size()));
    for (int k = 0; k < A[0].size(); ++ k)
        for (int i = 0; i < A.size(); ++ i)
            for (int j = 0; j < B[0].size(); ++ j)
                (ret[i][j] += A[i][k] * 1ll * B[k][j] % MOD) %= MOD;
    return ret;
}

int work() {
    mat R(n,vec(n));
    for (int i = 0; i < n; ++ i) {
        if (i != n - 1) {
            R[i][i + 1] = (n - 1 - i) % MOD;
        }

        R[i][i] = i % MOD;
    }
    mat L(1,vec(n));
    L[0][0] = det(A,n - 1);

    for ( ; q; q >>= 1) {
        if (q & 1) L = mul(L,R);
        R = mul(R,R);
    }
    return L[0][n - 1];
}

int main() {
    int cas;
    scanf("%d",&cas);
    while (cas--) {
        scanf("%d%d%d%d",&n,&m,&MOD,&q);
        memset(A,0,sizeof(A));
        for (int i = 0; i < m; ++ i) {
            int a,b;
            scanf("%d%d",&a,&b); a --; b --;
            A[a][a] ++;
            A[b][b] ++;
            A[a][b] --;
            A[b][a] --;
        }
        printf("%d\n",work());
    }
}
