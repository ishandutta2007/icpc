#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
typedef long long lld;
lld a,b,w,x,c;
lld calc(lld t) {
        if (t*x<=b) return 0;
        lld ret = 0;
        lld tmp = t*x-b;
        ret = tmp/w+(tmp%w!=0);
        return ret;
}
lld work() {
        if (c<=a) return 0;
        lld l = 0, r = (lld)2e12;
        lld ans = 0;
        while (l<=r) {
                lld mid = l+r>>1;
                if (mid>=calc(mid)+c-a) ans = mid, r = mid-1;
                else l = mid+1;
        }
        return ans;
}
int main() {
        scanf("%lld%lld%lld%lld%lld",&a,&b,&w,&x,&c);
        printf("%lld\n",work());
        return 0;
}
