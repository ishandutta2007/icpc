#include <bits/stdc++.h>
typedef long long LL;


LL work(LL a,LL b) {
    LL ret = 0;
    std::set<LL> set{a,b};
    while (b) {
        if (a > b) {
            ret += (a - b - 1) / (2 * b) * 2;
            a -= (a - b - 1) / (2 * b) * 2 * b;
        }
        if (a <= b) {
            a = b - a;
            b = b - a;
            set.insert(a);
        } else {
            b = a - b;
            a = a - b;
            set.insert(b);
        }
    }
    return ret + set.size();
}

int main() {
    int cas,ca = 0;
    scanf("%d",&cas);
    while (cas--) {
        LL a,b;
        scanf("%lld%lld",&a,&b);
        printf("Case #%d: %lld\n",++ca,work(a,b));
    }
}
