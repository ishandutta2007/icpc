#include <bits/stdc++.h>
using LL = long long ;

void my_assert(bool flag) {
    if (!flag) {
        printf("%d\n",1 / 0);
    }
}

LL p,q,r,b;
int L[5000],R[5000],tot;
int A[2500],B[2500];

inline void add(LL &a,LL b) {
    a += b;
    if (a >= r) a -= r;
}

LL mul(LL a,LL b) {
    LL ret = 0;
    for ( ; b; b >>= 1) {
        if (b & 1) add(ret,a);
        add(a,a);
    }
    return ret;
}

void construct(int u) {
    if (u < 2500) {
        A[u] = L[u];
        B[u] = R[u];
        return ;
    }
    construct(L[u]);
    std::swap(L[R[u]],R[R[u]]);
    construct(R[u]);
}

void work() {
    std::set<std::pair<LL,int>> set;
    p %= r;
    q %= r;
    b %= r;
    LL val = mul((p - q + r) % r,b);
    add(val,mul((r - val) % r,b));
    tot = 2500;
    LL b4 = mul(mul(mul(b,b),b),b);
    for (int i = 0; i < 2500; ++ i) {
        L[i] = 0;
        R[i] = 1;
        set.insert({val,i});
        val = mul(val,b4);
    }
    while (set.size() >= 2) {
        LL x = set.rbegin()->first;
        L[tot] = set.rbegin()->second;
        set.erase(*set.rbegin());
        LL y = set.rbegin()->first;
        R[tot] = set.rbegin()->second;
        set.erase(*set.rbegin());
        if (x < y) {
            std::swap(x,y);
            std::swap(L[tot],R[tot]);
        }
        tot ++;
        auto itr = set.lower_bound({x - y,-1});
        if (itr != set.end() && itr->first == x - y) {
            L[tot] = tot - 1;
            R[tot] = itr->second;
            memset(A,0,sizeof(A));
            memset(B,0,sizeof(B));
            construct(tot);
            for (int i = 0; i < 2500; ++ i) {
                if (A[i]) {
                    printf("()()");
                } else {
                    printf("(())");
                }
            }
            puts("");
            for (int i = 0; i < 2500; ++ i) {
                if (B[i]) {
                    printf("()()");
                } else {
                    printf("(())");
                }
            }
            puts("");
            return ;
        }
        set.insert({x - y,tot - 1});
    }
    my_assert(false);
}

int main() {
    while (scanf("%I64d%I64d%I64d%I64d",&p,&q,&r,&b) == 4) {
        work();
    }
}

