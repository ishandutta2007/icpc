/* Created Time: Monday, November 25, 2013 AM08:17:24 CST */
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
int n,k,dp[51000],bal = 25000;
int x[110],y[110];
int main() {
    scanf("%d%d",&n,&k);
    memset(dp,-1,sizeof(dp));
    dp[bal] = 0;
    for (int i = 0; i < n; i ++) scanf("%d",&x[i]);
    for (int i = 0; i < n; i ++) {
        scanf("%d",&y[i]);
        y[i] = x[i]-k*y[i];
    }
    for (int i = 0; i < n; i ++) {
        int a = x[i];
        int b = y[i];
        if (b>=0) {
            for (int j = 50000; j >= b; j --)
                if (dp[j-b]!=-1) dp[j] = max(dp[j-b]+a,dp[j]);
        } else {
            for (int j = 0; j <= 50000+b; j ++)
                if (dp[j-b]!=-1) dp[j] = max(dp[j-b]+a,dp[j]);
        }
    }
    if (dp[bal]==0) puts("-1");
    else printf("%d\n",dp[bal]);
    return 0;
}
