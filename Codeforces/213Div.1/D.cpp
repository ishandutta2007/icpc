#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
using namespace std;
typedef long long lld;
lld a[1201000],p[1300110];
int n,cnt[1300110],tot;
lld gcd(lld a,lld b) { return b==0 ? a : gcd(b,a%b); }
int main() {
        scanf("%d",&n);
        for (int i = 0; i < n; i ++) scanf("%lld",&a[i]);
        int fuck = 10;
        lld ans = 0;
        while (fuck--) {
                lld val = a[(rand()<<15|rand())%n];
                tot = 0;
                for (int i = 1; (lld)i*i <= val; i ++) if (val%i==0) {
                        p[tot++] = i;
                        if ((lld)i*i!=val) p[tot++] = val/i;
                }
                sort(p,p+tot);
                for (int i = 0; i < tot; i ++) cnt[i] = 0;
                for (int i = 0; i < n; i ++)
                        cnt[lower_bound(p,p+tot,gcd(val,a[i]))-p] ++;
                for (int i = 0; i < tot; i ++) if (ans<p[i]) {
                        for (int j = i+1; j < tot; j ++)
                                if (p[j]%p[i]==0) cnt[i] += cnt[j];
                        if (cnt[i]*2>=n) ans = p[i];
                }
        }
        printf("%lld\n",ans);
        return 0;
}
