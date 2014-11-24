#include <stdio.h>
#include <algorithm>
using namespace std;
const int N = 202000;
int n,a[N],cnt[N];
int main() {
        scanf("%d",&n);
        long long ans = 0;
        for (int i = 1; i <= n; i ++) {
                int x;
                scanf("%d",&x);
                cnt[i] = cnt[i-1]+(x==1);
                if (x==0) ans += cnt[i-1];
        }
        printf("%lld\n",ans);
        return 0;
}
