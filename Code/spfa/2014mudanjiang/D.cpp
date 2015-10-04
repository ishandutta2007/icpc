#include <bits/stdc++.h>

double dp[50 + 1][50 + 1][2500 + 1];
int vis[50 + 1][50 + 1][2500 + 1],tim;

int n,m;

double calc(int x,int y,int left) {
    if (x > n || y > m || left < 0)
        return 0.;
    if (x == n && y == m)
        return 0.;
    if (vis[x][y][left] == tim) 
        return dp[x][y][left];

    vis[x][y][left] = tim;
    dp[x][y][left] = 
        (x * (m - y) * calc(x,y + 1,left + x - 1)
         + (n - x) * y * calc(x + 1,y,left + y - 1)
         + (n - x) * (m - y) * calc(x + 1,y + 1,left + x + y)
         + left * calc(x,y,left - 1))
        / (n * m - x * y + left)
        + 1;
    return dp[x][y][left];
}

int main() {
    int cas;
    scanf("%d",&cas);
    while (cas--) {
        scanf("%d%d",&n,&m);
        ++ tim;
        printf("%.20f\n",calc(0,0,0));
    }
}
