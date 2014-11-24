/* Created Time: 2013年10月05日 星期六 00时49分33秒 */
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
const double eps = 1e-8;
int n,cnt,ans;
int a[4010];
int main() {
    scanf("%d",&n);
    n<<=1;
    for (int i = 0; i < n; i ++) {
        scanf("%*d.%d",&a[i]);
        if (a[i] == 0) cnt ++;
        ans += a[i];
    }
    ans -= (n>>1)*1000;
    while (ans <= -1000 && cnt) {
        cnt --;
        ans += 1000;
    }
    int tt = 1111111;
    int ug = 1111111;
    if (ans <= 0 && cnt) {
        tt = ans+1000;
        if (tt < 0) tt = -tt;
    }
    ans = abs(ans);
    ans = min(ans,tt);
    int x = ans/1000;
    ans %= 1000;
    printf("%d.%03d\n",x,ans);
    return 0;
}
