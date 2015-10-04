#include <stdio.h>
#include <string.h>
#include <algorithm>

const int N = 1000 + 5;
const int MOD = (int)1e9 + 7;

char X[N],Y[N];
int dp[N][N],len[N][N];
int n,m;
int next[N][26];

inline void add(int &a,int b) {
    a += b;
    if (a >= MOD) a -= MOD;
    if (a < 0) a += MOD;
}

int work() {
    n = strlen(X);
    m = strlen(Y);
    for (int i = 0; i <= m; ++ i) {
        for (int j = 0; j < 26; ++ j) {
            next[i][j] = -1;
        }
    }
    for (int i = m - 1; i >= 0; -- i) {
        for (int j = 0; j < 26; ++ j) {
            next[i][j] = next[i + 1][j];
        }
        next[i][Y[i] - 'a'] = i;
    }

    for (int i = 0; i <= n; ++ i) {
        for (int j = 0; j <= m; ++ j) {
            dp[i][j] = 0;
            len[i][j] = 0;
        }
    }
    dp[0][0] = 1;
    for (int i = 0; i <= n; ++ i) {
        for (int j = 0; j <= m; ++ j) {
            if (dp[i][j] == 0) continue;
            if (next[j][X[i] - 'a'] != -1) {
                int t = next[j][X[i] - 'a'] + 1;
                if (len[i + 1][t] < len[i][j] + 1) {
                    len[i + 1][t] = len[i][j] + 1;
                    dp[i + 1][t] = dp[i][j];
                } else if (len[i + 1][t] == len[i][j] + 1) {
                    add(dp[i + 1][t],dp[i][j]);
                }
            }
            if (len[i + 1][j] < len[i][j]) {
                len[i + 1][j] = len[i][j];
                dp[i + 1][j] = dp[i][j];
            } else if (len[i + 1][j] == len[i][j]) {
                add(dp[i + 1][j],dp[i][j]);
            }
        }
    }
    int mx = -1;
    for (int i = 0; i <= m; ++ i) {
        mx = std::max(mx,len[n][i]);
    }
    int ret = 0;
    for (int i = 0; i <= m; ++ i) {
        if (len[n][i] == mx) {
            add(ret,dp[n][i]);
        }
    }
    return ret;
}

int main() {
    int cas;
    scanf("%d",&cas);
    while (cas--) {
        scanf("%s%s",X,Y);
        printf("%d\n",work());
    }
}
