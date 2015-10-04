#include <stdio.h>
#include <string.h>
#include <algorithm>
typedef long long LL;

const int N = 50000 + 5;
int W[N];
int cnt[N];
int n,m;

LL gcd(LL a,LL b) {
    return b == 0 ? a : gcd(b,a % b);
}

int main() {
    int cas;
    scanf("%d",&cas);
    while (cas--) {
        scanf("%d%d",&n,&m);
        for (int i = 1; i <= n; ++ i) {
            scanf("%d",W + i);
            cnt[i] = 0;
        }
        cnt[0] = 0;
        for (int i = 0; i < m; ++ i) {
            int l,r;
            scanf("%d%d",&l,&r);
            cnt[r] ++;
            cnt[l - 1] --;
        }
        if (m < 3) {
            printf("0\n");
            continue;
        }
        for (int i = n - 1; i >= 1; -- i)
            cnt[i] += cnt[i + 1];
        LL sum = 0;
        for (int i = 1; i <= n; ++ i) {
            sum += W[i] * cnt[i] * 1ll * (cnt[i] - 1) * (cnt[i] - 2) / 6;
        }
        LL q = m * 1ll * (m - 1) * (m - 2) / 6;
        LL g = gcd(sum,q);
        if (q == g) {
            printf("%I64d\n",sum / g);
        } else {
            printf("%I64d/%I64d\n",sum / g,q / g);
        }
    }
}
