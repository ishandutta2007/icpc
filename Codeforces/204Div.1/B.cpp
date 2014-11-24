/* Created Time: 2013年10月05日 星期六 12时44分42秒 */
#include <stdio.h>
#include <string.h>
int n,a[3333],cnt;
int main() {
    scanf("%d",&n);
    for (int i = 0; i < n; i ++) {
        scanf("%d", &a[i]);
        for (int j = 0; j < i; j ++)
            if (a[j] > a[i]) cnt ++;
    }
    int ans = cnt/2*4;
    if (cnt&1) ans ++;
    printf("%d\n",ans);
    return 0;
}
