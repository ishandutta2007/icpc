#include <bits/stdc++.h>
typedef long long LL;

int a,b,c,l;

LL depart(int l,int r) {
    if (l < 0) l = 0;
    if (l > r) return 0;
    return (r - l + 1) + (l + r) * 1ll * (r - l + 1) / 2;
}

LL calc_max_a(int a,int b,int c,int l) {
    LL ret = 0;
    for (int i = 0; i <= l; ++ i) {
        int A = a + i;
        if (A > b && A > c) {
            ret += depart(A + 1 - b - c,l - i)
                - depart(A + 1 - A - c,l - i - (A - b))
                - depart(A + 1 - b - A,l - i - (A - c))
                + depart(A + 1 - A - A,l - i - (A - b) - (A - c));
        }
    }
    return ret;
}

LL calc_max_ab(int a,int b,int c,int l) {
    if (a < b) std::swap(a,b);
    l -= a - b;
    b = a;
    if (a < c + 1) {
        l -= c + 1 - a << 1;
        a = b = c + 1;
    }
    LL ret = 0;
    for (int i = 0; i * 2 <= l; ++ i) {
        int A = a + i;
        int left = l - i * 2;
        ret += std::min(A - 1 - c,left) + 1;
    }
    return ret;
}

LL calc_max_abc(int a,int b,int c,int l) {
    if (a < b) std::swap(a,b);
    if (a < c) std::swap(a,c);
    l -= a - b;
    b = a;
    l -= a - c;
    c = a;
    LL ret = 0;
    for (int i = 0; i * 3 <= l; ++ i)
        ret ++;
    return ret;
}

LL work() {
    return calc_max_a(a,b,c,l) + calc_max_a(b,a,c,l) + calc_max_a(c,a,b,l)
        + calc_max_ab(a,b,c,l) + calc_max_ab(a,c,b,l) + calc_max_ab(b,c,a,l)
        + calc_max_abc(a,b,c,l);
}

int main() {
    scanf("%d%d%d%d",&a,&b,&c,&l);
    printf("%I64d\n",work());
}
