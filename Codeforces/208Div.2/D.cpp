/* Created Time: Monday, November 25, 2013 PM03:47:20 CST */
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int N = 3333;
int n,c[N][3];
int dp[N][2];
int work() {
    dp[1][0] = c[1][1];
    dp[1][1] = c[1][0];
    for (int i = 2; i <= n; i ++) {
        dp[i][0] = max(dp[i-1][1]+c[i][2],dp[i-1][0]+c[i][1]);
        dp[i][1] = max(dp[i-1][0]+c[i][0],dp[i-1][1]+c[i][1]);
    }
    return dp[n][1];
}
int main() {
    scanf("%d",&n);
    for (int i = 0; i < 3; i ++) {
        for (int j = 1; j <= n; j ++) scanf("%d",&c[j][i]);
    }
    printf("%d\n",work());
    return 0;
}
