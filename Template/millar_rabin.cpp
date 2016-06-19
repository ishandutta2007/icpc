using LL = long long ;
LL mul_mod(LL a,LL b,LL c) {
    a %= c; b %= c;
    if (a == 0 || (LL)1e18 / a >= b) {
        return a * b % c;
    }
    LL ret = 0;
    while (b) {
        if (b & 1) {
            ret += a;
            if (ret >= c) ret -= c;
        }
        a <<= 1;
        b >>= 1;
        if (a >= c) a -= c;
    }
    return ret;
}

LL pow_mod(LL x,LL n,LL mod) {
    LL ret = 1;
    while (n) {
        if (n & 1) ret = mul_mod(ret,x,mod);
        x = mul_mod(x,x,mod);
        n >>= 1;
    }
    return ret;
}

bool check(LL a,LL n,LL x,LL t) { // 以a为基,n-1==x*2^t,检验n是不是合数
    LL ret = pow_mod(a,x,n),last = ret;
    for (int i = 1; i <= t; ++ i) {
        ret = mul_mod(ret,ret,n);
        if (ret == 1 && last != 1 && last != n - 1) return true;
        last = ret;
    }
    if (ret != 1) return true;
    return false;
}

bool miller_rabin(LL n) { // 检验n是不是合数
    LL x = n - 1,t = 0;
    while (~x & 1) x >>= 1,++ t;
    bool flag = true;
    if (t >= 1 && (x & 1)) {
        std::vector<LL> cs{2, 325, 9375, 28178, 450775, 9780504, 1795265022};
        for (LL a : cs) {
            if (check(a,n,x,t)) {
                flag = true;
                break;
            }
            flag = false;
        }
    }
    if (!flag || n == 2) return false;
    return true;
}
