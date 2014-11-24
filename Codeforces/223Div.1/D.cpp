#include <cstdio>
#include <algorithm>
using namespace std;
const int N = 101000,MOD = 1e9+7;
typedef long long lld;
lld inv[N],Finv[N],F[N];
int n,time[N];
lld C(int a,int b) {
        if (a<b) return 0;
        return F[a]*Finv[b]%MOD*Finv[a-b]%MOD;
}
lld work() {
        lld ll,rr,pre,pos,cnt;
        ll = 1; rr = 1; pre = -1; pos = -1; cnt = 0;
        for (int i = 1; i <= n; i ++) {
         //       printf("%I64d %I64d %I64d %I64d %I64d\n",ll,rr,pre,pos,cnt);
                if (time[i]==0) cnt ++;
                else {
                        int cur = time[i],a,b;
                        lld nexl = 0,nexr = 0;
                        if (pre==-1) {
                                if (cnt==0) {
                                        nexl = 1;
                                } else {
                                        a = cur-1;
                                        b = n-cur;
                                        if (a>=cnt) {
                                                for (int i = 1; i <= cnt; i ++)
                                                        nexr = (nexr+C(cnt-1,i-1))%MOD;
                                        }
                                        if (b>=cnt) {
                                                for (int i = 1; i <= cnt; i ++)
                                                        nexl = (nexl+C(cnt-1,i-1))%MOD;
                                        }
                                }
                        } else {
                                if (cur<pos) {
                                        a = pos-1-cur;
                                        b = n-pos-pre+1;
                                        if (a>=0 && b>=0 && cnt>=a && a+b>=cnt) {
                                                nexl = (nexl+C(cnt,a)*ll%MOD)%MOD;
                                        }
                                        a = pos-1-cur-pre+1;
                                        b = n-pos;
                                        if (a>=0 && b>=0 && cnt>=a && a+b>=cnt) {
                                                nexl = (nexl+C(cnt,a)*rr%MOD)%MOD;
                                        }
                                } else if (cur>pos) {
                                        a = cur-1-pos;
                                        b = pos-pre;
                                        if (a>=0 && b>=0 && cnt>=a && a+b>=cnt) {
                                                nexr = (nexr+C(cnt,a)*rr%MOD)%MOD;
                                        }
                                        a = cur-1-pos-pre+1;
                                        b = pos-1;
                                        if (a>=0 && b>=0 && cnt>=a && a+b>=cnt) {
                                                nexr = (nexr+C(cnt,a)*ll%MOD)%MOD;
                                        }
                                }
                        }
                        pos = cur;
                        pre = i;
                        ll = nexl;
                        rr = nexr;
                        cnt = 0;
                }
        }
        if (cnt==n) {
                lld ret = 1;
                for (int i = 0; i < n-1; i ++)
                        ret = ret*2%MOD;
                return ret;
        }
        int a,b;
        a = pos-pre;
        b = n-pos;
        if (a>=0 && b>=0) {
                rr = rr*C(cnt,a)%MOD;
        }
        a = pos-1;
        b = n-pos-pre+1;
        if (a>=0 && b>=0) {
                ll = ll*C(cnt,a)%MOD;
        }
        return (ll+rr)%MOD;
}
int main() {
        inv[1] = 1;
        for (int i = 2; i < N; i ++) inv[i] = (MOD-MOD/i)*inv[MOD%i]%MOD;
        Finv[0] = F[0] = 1;
        for (int i = 1; i < N; i ++) {
                F[i] = F[i-1]*i%MOD;
                Finv[i] = Finv[i-1]*inv[i]%MOD;
        }
        scanf("%d",&n);
        for (int i = 1; i <= n; i ++) {
                int x;
                scanf("%d",&x);
                time[x] = i;
        }
        printf("%lld\n",work());
        return 0;
}
