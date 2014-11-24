#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <map>
using namespace std;
typedef long long lld;
const int N = 101000,MOD = 1e9+7;;
int n,prm[N],ptot;
lld F[N],Finv[N],inv[N];
map<int,int> mp;
void init() {
        for (int i = 2; i < N; i ++) if (!prm[i]) {
                prm[ptot++] = i;
                for (int j = i+i; j < N; j += i) prm[j] = 1;
        }
        F[0] = Finv[0] = inv[1] = 1;
        for (int i = 2; i < N; i ++) {
                inv[i] = (MOD-MOD/i)*inv[MOD%i]%MOD;
        }
        for (int i = 1; i < N; i ++) {
                F[i] = F[i-1]*i%MOD;
                Finv[i] = Finv[i-1]*inv[i]%MOD;
        }
}
void sol(int x) {
        int p = 0;
        while (x>1 && p<ptot) {
                if (x%prm[p]==0) {
                        x /= prm[p];
                        mp[prm[p]] ++;
                } else p ++;
        }
        if (x>1) mp[x] ++;
}
lld C(int a,int b) {
        if (a<b) return 0;
        return F[a]*Finv[a-b]%MOD*Finv[b]%MOD;
}
int main() {
        init();
        scanf("%d",&n);
        for (int i = 0; i < n; i ++) {
                int x;
                scanf("%d",&x);
                sol(x);
        }
        lld ans = 1;
        for (map<int,int>::iterator it = mp.begin(); it != mp.end(); it ++) {
                ans = ans*C(it->second+n-1,n-1)%MOD;
        }
        printf("%lld\n",ans);
        return 0;
}