/* Created Time: Thursday, November 14, 2013 PM11:29:45 CST */
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
char mark[8][8];
int x[2],y[2],tot;
bool vis[8][8];
int cnt[8][8];
int dir[4][2] = {2,2,-2,2,2,-2,-2,-2};
int qx[110],qy[110];
bool work() {
    tot = 0;
    for (int i = 0; i < 8; i ++)
        for (int j = 0; j < 8; j ++) {
            if (mark[i][j]=='K') {
                x[tot] = i;
                y[tot] = j;
                tot ++;
            }
        }
    memset(vis,0,sizeof(vis));
    memset(cnt,0,sizeof(cnt));
    int qf = 0,qe = -1;
    qx[++qe] = x[0];
    qy[qe] = y[0];
    vis[x[0]][y[0]] = true;
    while (qf<=qe) {
        int fx = qx[qf];
        int fy = qy[qf++];
        for (int i = 0; i < 4; i ++) {
            int ex = fx+dir[i][0];
            int ey = fy+dir[i][1];
            if (ex<0 || ex>=8 || ey<0 || ey>=8) continue;
            if (vis[ex][ey]) continue;
            cnt[ex][ey] = cnt[fx][fy]+1;
            if (ex==x[1] && ey==y[1]) 
                return cnt[ex][ey]%2==0;
            qx[++qe] = ex;
            qy[qe] = ey;
            vis[ex][ey] = 1;
        }
    }
    return false;
}
int main() {
    int cas;
    scanf("%d",&cas);
    while (cas--) {
        for (int i = 0; i < 8; i ++) 
            scanf("%s",mark[i]);
        puts(work() ? "YES" : "NO");
    }
    return 0;
}