#include <bits/stdc++.h>
typedef long long LL;

const int N = 100000 + 5;
int n,m;
char str[N];
LL dp[N][4]; // 0,0  0,1 1,0 1,1

LL work() {
    dp[0][0] = 1;
    for (int i = 0; i < n; ++ i) {
        for (int j = 0; j < 4; ++ j) {
            if (dp[i][j] == 0) continue;
            for (int c = 0; c < m; ++ c) {
                char ch = c + 'a';
                if (ch == str[i]) {
                    dp[i + 1][j] += dp[i][j];
                } else {
                    if (ch != str[i + 1]) {
                        if (~j & 1) {
                            dp[i + 1][j | 1] += dp[i][j];
                        }
                        if (j == 0) {
                            dp[i + 2][3] += dp[i][j];
                        }
                    } else {
                        if (~j >> 1 & 1) {
                            dp[i + 2][j | 2] += dp[i][j];
                        } else if (~j & 1) {
                            dp[i][j | 1] += dp[i][j];
                        }
                    }
                }
            }
        }
    }
    return dp[n][3] + dp[n][2] + dp[n - 1][1];
}

int main() {
    scanf("%d%d",&n,&m);
    scanf("%s",str);
    printf("%I64d\n",work());
}
