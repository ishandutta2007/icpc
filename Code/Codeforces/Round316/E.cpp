#include <bits/stdc++.h>
typedef long long LL;

const int MOD = (int)1e9 + 7;
const int N = 500 + 5;
char str[N][N];
int n,m;
int dir[4][2] = {1,0,0,1,-1,0,0,-1};
int dp[2][N][N];

inline LL encode(int a,int b,int c,int d) {
    return (a * m + b) * 1ll * n * m + c * m + d;
}

inline void add(int &a,int b) {
    a += b;
    if (a >= MOD) a -= MOD;
}

int work() {
    if (str[0][0] != str[n - 1][m - 1]) {
        return 0;
    }
    dp[0][0][n - 1] = 1;
    int step = -1;
    if (n + m - 1 & 1) {
        step = n + m - 2 >> 1;
    } else {
        step = (n + m - 1 >> 1) - 1;
    }
    for (int s = 0; s < step; ++ s) {
        int cur = s & 1;
        int nex = cur ^ 1;
        for (int i = 0; i < n; ++ i) {
            for (int j = 0; j < n; ++ j) {
                if (dp[cur][i][j] == 0) continue;
                int a = i;
                int b = s - i;
                int c = j;
                int d = (m - 1) - (s - (n - 1 - j));
                for (int ii = 0; ii < 2; ++ ii) {
                    int ta = a + dir[ii][0];
                    int tb = b + dir[ii][1];
                    if (ta < 0 || ta >= n || tb < 0 || tb >= m) continue;
                    for (int jj = 2; jj < 4; ++ jj) {
                        int tc = c + dir[jj][0];
                        int td = d + dir[jj][1];
                        if (tc < 0 || tc >= n || td < 0 || td >= m) continue;
                        if (ta > tc || tb > td) continue;
                        if (str[ta][tb] != str[tc][td]) continue;
                        add(dp[nex][ta][tc],dp[cur][i][j]);
                    }
                }
                dp[cur][i][j] = 0;
            }
        }
    }
    int answer = 0;
    for (int i = 0; i < n; ++ i) {
        for (int j = 0; j < n; ++ j) {
            add(answer,dp[step & 1][i][j]);
        }
    }
    return answer;
}

int main() {
    scanf("%d%d",&n,&m);
    for (int i = 0; i < n; ++ i) {
        scanf("%s",str[i]);
    }
    printf("%d\n",work());
}
