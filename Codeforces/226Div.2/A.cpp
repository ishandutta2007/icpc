#include <stdio.h>
int main() {
        int n,c;
        int pre,ans = 0;
        scanf("%d%d",&n,&c);
        for (int i = 0; i < n; i ++) {
                int x;
                scanf("%d",&x);
                if (i) {
                        int tmp = pre-x-c;
                        if (tmp>ans) ans = tmp;
                }
                pre = x;
        }
        printf("%d\n",ans);
        return 0;
}
