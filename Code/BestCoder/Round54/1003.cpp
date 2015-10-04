#include <stdio.h>
typedef long long LL;

LL gcd(LL a,LL b) {
    return b == 0 ? a : gcd(b,a % b);
}

LL n;

LL work() {
    if (n == 1) return 1;
    LL ret = 0;
    for (int k = 1; k * 2 < n + 1; ++ k) {
        if (gcd(k,n + 1) == 1)
            ret += 2;
    }
    return ret;
}

int main() {
    int cas;
    scanf("%d",&cas);
    while (cas--) {
        scanf("%d",&n);
        printf("%I64d\n",work());
    }
}
