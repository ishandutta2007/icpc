#include <stdio.h>
#include <string.h>
#include <algorithm>

const int N = 1000 + 5;
const int MOD = (int)1e9 + 7;

int n,p;
int A[N];
int dp[2][N];

inline void add(int &a,int b) {
    a += b;
    if (a >= MOD) a -= MOD;
}

int work() {
    memset(dp,0,sizeof(dp));
    dp[0][0] = 1;
    for (int i = 0; i < n; ++ i) {
        int cur = i & 1;
        int nex = cur ^ 1;
        for (int j = 0; j < p; ++ j) {
            add(dp[nex][(j + A[i]) % p],dp[cur][j]);
            add(dp[nex][j],dp[cur][j]);
            dp[cur][j] = 0;
        }
    }
    return dp[n & 1][0];
}

int main() {
    int cas;
    scanf("%d",&cas);
    while (cas--) {
        scanf("%d%d",&n,&p);
        for (int i = 0; i < n; ++ i) {
            scanf("%d",A + i);
            A[i] = (A[i] % p + p) % p;
        }
        printf("%d\n",work());
    }
}
