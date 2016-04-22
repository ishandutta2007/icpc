/*
   令f(lambda) = det(lambda * E - M)
   显然 f(M) == 0
   展开f(M)得到M^i == sum_{j=1}^{deg}{c(j) * M^{i-j}}
   然后快速幂blablah，复杂度O(deg^2 * log(n))
 */
typedef long long LL;
const int N = 2000 + 5;
const int MOD = (int)1e9 + 7;

LL n;
int D[N],D[N],deg;
struct Poly {
    int A[N];
    Poly() {
        memset(A,0,sizeof(A));
    }
    int& operator [] (int x) {
        return A[x];
    }
};
inline void add(int &a,int b) {
    a += b;
    if (a >= MOD) a -= MOD;
}
Poly operator * (Poly &X,Poly &Y) {
    Poly ret;
    for (int i = 0; i < deg; ++ i) 
        for (int j = 0; j < deg; ++ j) 
            add(ret[i + j],X[i] * 1ll * Y[j] % MOD);
    for (int i = deg + deg - 2; i >= 0; -- i) {
        for (int j = 1; j <= deg; ++ j)
            add(ret[i - j],ret[i] * 1ll * C[j] % MOD);
        ret[i] = 0;
    }
    return ret;
}
int work() {
    memset(C,0,sizeof(C));
    memset(D,0,sizeof(D));
    deg = 2;
    D[0] = 3; D[1] = 4;
    C[2] = 1; C[1] = 2;
    n = 3;
    /* C为转移关系，D为初值，deg为阶数 */
    // F(i) = 2 * F(i-1) + 1 * F(i-2)
    // F0 = 3 , F1 = 4 , F2 = 11 , F3 = 25...
    Poly ans,P;
    P[1] = 1,ans[0] = 1;
    while (n) {
        if (n & 1) ans = ans * P;
        P = P * P;
        n >>= 1;
    }
    int ret = 0;
    for (int i = 0; i < deg; ++ i)
        add(ret,D[i] * 1ll * ans[i] % MOD);
    return ret;
}
