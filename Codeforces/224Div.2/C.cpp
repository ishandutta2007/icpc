#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <vector>
using namespace std;
const int N = 101000;
int n,a[N];
void work() {
        if (n==1) {
                puts("-1"); return ;
        }
        int dt = a[1]-a[0];
        vector<int> ans;
        if (n==2) {
                if (dt%2==0) ans.push_back(a[0]+dt/2);
        }
        for (int i = 0; i < n-1; i ++) dt = min(dt,a[i+1]-a[i]);
        int p = -1;
        bool can = true;
        for (int i = 0; i < n-1; i ++) {
                if (a[i+1]-a[i]!=dt) {
                        if ((a[i+1]-a[i])%2==0 && (a[i+1]-a[i])/2==dt && can) {
                                can = false;
                                ans.push_back(a[i]+dt);
                        } else {
                                puts("0");
                                return ;
                        }
                }
        }
        if (can) {
                ans.push_back(a[0]-dt);
                ans.push_back(a[n-1]+dt);
        }
        sort(ans.begin(),ans.end());
        ans.erase(unique(ans.begin(),ans.end()),ans.end());
        printf("%d\n",(int)ans.size());
        for (int i = 0; i < (int)ans.size(); i ++) printf("%d ",ans[i]);
        puts("");
}
int main() {
        scanf("%d",&n);
        for (int i = 0; i < n; i ++) scanf("%d",&a[i]);
        sort(a,a+n);
        work();
        return 0;
}
