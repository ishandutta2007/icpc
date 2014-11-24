#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
bool vis[10001000];
int mindiv[10001000],p[10001000],ptot,cnt[10001000];
void get_prim(int n) {
        vis[1] = mindiv[1] = 1;
        for (int i = 2; i <= n; i ++) {
                if (!vis[i]) p[ptot++] = i,mindiv[i] = i;
                for (int j = 0; j < ptot; j ++) {
                        if (i*p[j]>n) break;
                        vis[i*p[j]] = 1;
                        mindiv[i*p[j]] = p[j];
                        if (i%p[j]==0) break;
                }
        }
}
int main() {
        get_prim(10000000);
        int n,m,l,r,x;
        scanf("%d",&n);
        for (int i = 0; i < n; i ++) {
                scanf("%d",&x);
                while (x>1) {
                        int cur = mindiv[x];
                        cnt[cur] ++;
                        while (x%cur==0) x /= cur;
                }
        }
        for (int i = 2; i <= 10000000; i ++) cnt[i] += cnt[i-1];
        scanf("%d",&m);
        while (m--) {
                scanf("%d%d",&l,&r);
                l = min(l,10000000);
                r = min(r,10000000);
                printf("%d\n",cnt[r]-cnt[l-1]);
        }
        return 0;
}
