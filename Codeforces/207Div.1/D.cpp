#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;

const int N = 77777;
bool f[N],belong[N];
int pre[N],ans[N],child[N],n,s,arr[N];
pair<int,int> a[N];

int main() {
        scanf("%d%d",&n,&s);
        for (int i = 0; i < n; i ++) {
                scanf("%d",&a[i].first);
                a[i].second = i;
        }
        sort(a,a+n);
        reverse(a,a+n);
        if (a[0].first>s) { puts("-1"); return 0; }
        f[a[0].first] = 1;
        memset(pre,-1,sizeof(pre));
        pre[a[0].first] = 0;
        arr[0] = a[0].first;
        int l,r;
        l = r = 0;
        for (int i = 1; i < n; i ++) {
                int rr = r;
                for (int j = l; j <= rr; j ++) {
                        int val = arr[j]+a[i].first;
                        if (val<=s && !f[val]) {
                                f[val] = 1;
                                arr[++r] = val;
                                pre[val] = i;
                        }
                }
                if (f[s]) break;
                if (i!=n-1 && a[i].first==a[i+1].first) l = rr+1;
                else l = 0;
        }
        if (pre[s]==-1) { puts("-1"); return 0; }
        while (pre[s]!=-1) {
                belong[pre[s]] = true;
                s -= a[pre[s]].first;
        }
        for (int i = 0; i < n; i ++) {
                ans[a[i].second] = a[i].first;
                if (!belong[i]) {
                        ans[a[i-1].second] -= a[i].first;
                        child[a[i-1].second] = a[i].second+1;
                }
        }
        for (int i = 0; i < n; i ++) {
                printf("%d ",ans[i]);
                if (child[i]) printf("1 %d\n",child[i]);
                else printf("0\n");
        }
        return 0;
}
