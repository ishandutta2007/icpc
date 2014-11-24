#include <stdio.h>
#include <string.h>
typedef long long lld;
const int N = 1010000;
lld cnt[N][26],n,m;
char a[N],b[N];
lld gcd(lld a,lld b) { return b==0 ? a : gcd(b,a%b); }
lld work() {
        lld lena = strlen(a);
        int lenb = strlen(b);
        lld g = gcd(lena,lenb);
        lld lcm = lena/g*lenb;
        lld ret = lcm;
        for (int i = 0; i < lenb; i ++)
                cnt[i%g][b[i]-'a'] ++;
        for (int i = 0; i < lena; i ++)
                ret -= cnt[i%g][a[i]-'a'];
        return ret * (n*lena/lcm);
}
int main(){
        scanf("%lld%lld",&n,&m);
        scanf("%s%s",a,b);
        printf("%lld\n",work());
        return 0;
}
