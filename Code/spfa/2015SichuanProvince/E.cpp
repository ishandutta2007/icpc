#include <stdio.h>
#include <string.h>
#include <algorithm>
typedef long long LL;

int n,m,K;

LL work() {
    LL ret = 0;
    for (int i = 1; i <= std::min(n,K - 2 >> 1); ++ i) {
        int t = K / 2 - i;
        LL tmp = 0;
        if (t < m) {
            tmp += (m - t) * 1ll * t;
        } else {
            t = m;
        }
        tmp += t * 1ll * (t + 1) / 2;

        ret += tmp * (n - i + 1);
    }
    return ret;
}

int main() {
    while (scanf("%d%d%d",&n,&m,&K) == 3) {
        printf("%lld\n",work());
    }
}
