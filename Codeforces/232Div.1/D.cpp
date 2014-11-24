#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
typedef long long lld;
const int N = 1001000,MOD = 1e9+7;
int n,a[N];
lld D[N],C[N],B[N],A[N];
void modify(int p,lld dt) {
        for (int i = p; i < N; i += i&-i) (B[i] += dt) %= MOD;
}
lld query(int p) {
        lld ret = 0;
        for (int i = p; i > 0; i -= i&-i) (ret += B[i]) %= MOD;
        return ret;
}
int main() {
        scanf("%d",&n);
        for (int i = 1; i <= n; i ++) scanf("%d",&a[i]);
        A[0] = 1;
        for (int i = 1; i < N; i ++) A[i] = A[i-1]*i%MOD;
        for (int i = 1; i < N; i ++) D[i] = (D[i-1]+i)%MOD;
        for (int i = 2; i < N; i ++)
                C[i] = (C[i-1]*i%MOD+(lld)i*(i-1)/2%MOD*A[i-1]%MOD)%MOD;
        lld ans = 0,cnt = 0;
        for (int i = 1; i <= n; i ++) {
                lld bp = query(n)-query(a[i]);
                lld sn = a[i]-1-query(a[i]);
                ans = (ans+bp)%MOD;
                if (sn>0) {
                        ans = (ans+D[sn-1]*A[n-i]%MOD)%MOD;
                        ans = (ans+sn*cnt%MOD*A[n-i]%MOD)%MOD;
                        ans = (ans+sn*C[n-i]%MOD)%MOD;
                }
                cnt = (cnt+sn)%MOD;
//                printf("bp=%lld sn=%lld ans=%lld cnt=%lld\n",bp,sn,ans,cnt);
                modify(a[i],1);
        }
        printf("%lld\n",ans);
        return 0;
}