/* Created Time: Tuesday, November 19, 2013 AM11:53:01 CST */
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
typedef long long lld;
int n,m;
lld budget;
const int N = 101000;
lld b[N],p[N];
void work() {
    sort(b,b+n);
    sort(p,p+m);
    int l = 1,r = min(n,m),ans = 0;
    while (l<=r) {
        int mid = l+r>>1;
        lld left = budget;
        for (int i = 0; i < mid; i ++) {
            lld fuc = b[n-mid+i]-p[i];
            if (fuc<0) left += fuc;
        }
        if (left>=0) ans = mid,l = mid+1;
        else r = mid-1;
    }
    if (ans==0) {
        puts("0 0");
        return ;
    }
    lld ans2 = 0,total = 0;
    for (int i = n-ans; i < n; i ++)
        total += p[i-n+ans];
    budget -= total;
    if (budget<0) ans2 = -budget;
    printf("%d %lld\n",ans,ans2);
}
int main() {
    scanf("%d%d%lld",&n,&m,&budget);
    for (int i = 0; i < n; i ++)
        scanf("%lld",&b[i]);
    for (int i = 0; i < m; i ++)
        scanf("%lld",&p[i]);
    work();
    return 0;
}
