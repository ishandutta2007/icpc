#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
typedef long long lld;
const int N = 101000;
int n,m;
lld a[N],b[N];
bool check(lld day) {
        int p = 0;
        for (int i = 0; i < n; i ++) {
                int j;
                for (j = p; j < m; j ++) 
                        if (abs(b[p]-a[i])+b[j]-b[p]<=day ||  abs(b[j]-a[i])+b[j]-b[p]<=day);
                        else
                                break;
                p = j;
        }
        return p==m;
}
int main() {
        scanf("%d%d",&n,&m);
        for (int i = 0; i < n; i ++) scanf("%lld",a+i);
        for (int i = 0; i < m; i ++) scanf("%lld",b+i);
        lld l = 0,r = (lld)2e10;
        while (l<=r) {
                lld mid = l+r>>1;
                if (check(mid)) r = mid-1;
                else l = mid+1;
        }
        printf("%lld\n",r+1);
        return 0;
}
