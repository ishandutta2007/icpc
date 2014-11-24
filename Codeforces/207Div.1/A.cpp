/* Created Time: 2013年10月16日 星期三 09时55分26秒 */
#include <stdio.h>
int fa[301000],ans[301000];
int Find(int x) { return x==fa[x]? x:fa[x]=Find(fa[x]); }
int main() {
        int n,m;
        scanf("%d%d",&n,&m);
        for (int i = 1; i <= n+1; i ++) fa[i] = i;
        while (m--) {
                int l,r,x;
                scanf("%d%d%d",&l,&r,&x);
                for (int p = Find(l); p <= r; p = Find(p+1)) {
                        if (p!=x) {
                                fa[p] = p+1;
                                ans[p] = x;
                        }
                }
        }
        for (int i = 1; i <= n; i ++) 
                printf("%d%c",ans[i],i==n?'\n':' ');
        return 0;
}
