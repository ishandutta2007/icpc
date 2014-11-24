#include <cstdio>
const int N = 55;
int n,m,q,s[N][N];
char mat[N][N];
int dp[N][N][N][N]; // x1,y1,x2,y2
bool check(int a,int b,int c,int d) {
        return (s[c][d]-s[c][b-1]-s[a-1][d]+s[a-1][b-1])==0;
}
void presolve() {
        for (int j = 1; j <= m; j ++)
                for (int i = 1; i <= n; i ++) s[i][j] = s[i-1][j]+(mat[i][j]=='1');
        for (int i = n; i >= 1; i --)
                for (int j = 1; j <= m; j ++) s[i][j] += s[i][j-1];

        // 固定左右界
        for (int ly = 1; ly <= m; ly ++)
                for (int j = 1; j <= m-ly+1; j ++) {
                        int jj = j+ly-1;
                        int len = 0;
                        int cnt[N] = {0};
                        for (int i = 1; i <= n; i ++) {
                                dp[1][j][i][jj] = dp[1][j][i-1][jj];
                                if (check(i,j,i,jj)) dp[1][j][i][jj] += ++len;
                                else len = 0;
                                for (int r = 1; r<len; r ++) cnt[i-r] += len-r;
                                for (int r = 1; r <= i; r ++)
                                        dp[r][j][i][jj] = dp[1][j][i][jj]-dp[1][j][r-1][jj]-cnt[r-1];
                        }
                }
        // 固定左界
        for (int lx = 1; lx <= n; lx ++)
                for (int i = 1; i <= n-lx+1; i ++) {
                        int ii = i+lx-1;
                        for (int j = 1; j <= m; j ++)
                                for (int jj = j; jj <= m; jj ++)
                                        dp[i][j][ii][jj] += dp[i][j][ii][jj-1];
                }
        // 无界
        for (int lx = 1; lx <= n; lx ++)
                for (int i = 1; i <= n-lx+1; i ++) {
                        int ii = i+lx-1;
                        for (int jj = 1; jj <= m; jj ++)
                                for (int j = jj; j >= 1; j --)
                                    dp[i][j][ii][jj] += dp[i][j+1][ii][jj];
                }
}
int main() {
        scanf("%d%d%d",&n,&m,&q);
        for (int i = 1; i <= n; i ++) scanf("%s",mat[i]+1);
        presolve();
        while (q--) {
                int a,b,c,d;
                scanf("%d%d%d%d",&a,&b,&c,&d);
                printf("%d\n",dp[a][b][c][d]);
        }
        return 0;
}
