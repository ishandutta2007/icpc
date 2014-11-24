#include <stdio.h>
const int N = 22010,MOD = 1e9+7;
int n,dp[2][N],bal = 11000,cur,nex;
int main() {
        scanf("%d",&n);
        cur = 0; nex = 1;
        int L = 1000,R = 21000,ans = 0;
        for (int i = 0; i < n; i ++) {
                int val;
                scanf("%d",&val);
                dp[cur][bal] ++;
                for (int j = L; j <= R; j ++)
                        dp[nex][j] = (dp[cur][j-val]+dp[cur][j+val])%MOD;
                ans = (ans+dp[nex][bal])%MOD;
                cur ^= 1; nex ^= 1;
        }
        printf("%d\n",ans);
        return 0;
}
