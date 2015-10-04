#include <stdio.h>
#include <string.h>
#include <algorithm>
typedef long long LL;

int work(int m) {
    int ret = 0;
    while (m) {
        int l = 1,r = 100000;
        while (l <= r) {
            int mid = l + r >> 1;
            LL t = 3 * mid * 1ll * (mid - 1) + 1;
            if (t > m) r = mid - 1;
            else l = mid + 1;
        }
        l --;
        int t = 3 * l * (l - 1) + 1;
        ret += m / t;
        m %= t;
    }
    return ret;
}

int main() {
    int cas;
    scanf("%d",&cas);
    while (cas--) {
        int m;
        scanf("%d",&m);
        printf("%d\n",work(m));
    }
}
