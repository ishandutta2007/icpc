/*
    let f(lambda) = det(lambda * E - M)
    obviously f(M) == 0
    expand f(M) we have M^i == sum_{j=1}^{deg}{coef(j) * M^{i-j}}
    complexity O(deg^2 * log(n))
    */

using LL = long long ;
using Poly = std::vector<int>;
const int MOD = (int)1e9 + 7;
inline void add(int &a, int b) { a += b; if (a >= MOD) a -= MOD; }
inline int mul(int x) { return x; }
template<typename ...Args> inline int mul(int x, Args ...args) { return x * 1LL * mul(args...) % MOD; }

void add(Poly &lhs, const Poly &rhs)
{
    for (int i = 0; i < lhs.size(); ++ i)
        add(lhs[i], rhs[i]);
}

Poly product(const Poly &lhs, const Poly &rhs, const Poly &coef)
{
    int deg = lhs.size();
    Poly ret(deg << 1);
    for (int i = 0; i < deg; ++ i) 
        for (int j = 0; j < deg; ++ j) 
            add(ret[i + j], mul(lhs[i], rhs[j]));
    for (int i = deg + deg - 2; i >= deg; -- i) {
        for (int j = 1; j < deg; ++ j)
            add(ret[i - j], mul(ret[i], coef[j]));
        ret[i] = 0;
    }
    ret.resize(deg);
    return ret;
}

Poly power(Poly P, LL n, const Poly &coef)
{
    Poly ret(P.size());
    ret[0] = 1;
    while (n) {
        if (n & 1) ret = product(ret, P, coef);
        P = product(P, P, coef);
        n >>= 1;
    }
    return ret;
}

int sample()
{
    LL n = 3;
    int deg = 3;
    Poly W(deg), coef(deg);
    coef[2] = 1; coef[1] = 2;
    W[0] = 3; W[1] = 4;
    // W_i = 2 * W_{i-1} + 1 * W_{i - 2}
    // W_0 = 3, W_1 = 4, W_2 = 11, W_3 = 25 ...

    Poly P(deg);
    P[1] = 1;
    Poly A = power(P, n, coef);
    int ret = 0;
    for (int i = 0; i < deg; ++ i)
        add(ret, mul(W[i], coef[i]));

    return ret;
}
