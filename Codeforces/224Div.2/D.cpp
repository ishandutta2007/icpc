#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
const int N = 2003;
char s[N][N];
int n,m,ans1,ans2,f[N][N];
bool vis[N][N];
void modify(int val) {
        if (val>ans2) {
                ans2 = val;
                if (ans2>ans1) swap(ans2,ans1);
        }
}
bool in(int x,int y) {
        if (x<0 || x >= n || y<0 || y >= m) return false;
        return true;
}
void fuck(int val,int &cnt,int &mx) {
        if (val>mx) cnt = 1,mx = val;
        else if (val==mx) cnt ++;
}
bool ok(int x,int y) {
        int cnt = 0,mx = 0;
        if (in(x,y+1) && s[x][y+1]=='<') fuck(f[x][y+1],cnt,mx);
        if (in(x,y-1) && s[x][y-1]=='>') fuck(f[x][y-1],cnt,mx);
        if (in(x+1,y) && s[x+1][y]=='^') fuck(f[x+1][y],cnt,mx);
        if (in(x-1,y) && s[x-1][y]=='v') fuck(f[x-1][y],cnt,mx);
        return cnt>=2;
}
void move(int x,int y) {
        int step = 0;
        vis[x][y] = true;
        while (s[x][y]!='#') {
                if (s[x][y]=='>') y ++;
                else if (s[x][y]=='<') y --;
                else if (s[x][y]=='^') x --;
                else if (s[x][y]=='v') x ++;
                vis[x][y] = true;
                f[x][y] = max(f[x][y],++step);
        }
}
int du(int x,int y) {
        int cnt = 0;
        if (in(x,y+1) && s[x][y+1]=='<') cnt ++;
        if (in(x,y-1) && s[x][y-1]=='>') cnt ++;
        if (in(x+1,y) && s[x+1][y]=='^') cnt ++;
        if (in(x-1,y) && s[x-1][y]=='v') cnt ++;
        return cnt;
}
int main() {
        scanf("%d%d",&n,&m);
        for (int i = 0; i < n; i ++) scanf("%s",s[i]);
        for (int i = 0; i < n; i ++)
                for (int j = 0; j < m; j ++)
                        if (s[i][j]=='>' && s[i][j+1]=='<'
                            || s[i][j]=='<' && s[i][j-1]=='>'
                            || s[i][j]=='^' && s[i-1][j]=='v'
                            || s[i][j]=='v' && s[i+1][j]=='^') {
                                puts("-1"); return 0;
                            }
        for (int i = 0; i < n; i ++)
                for (int j = 0; j < m; j ++)
                        if (!vis[i][j] && du(i,j)==0) move(i,j);
        for (int i = 0; i < n; i ++)
                for (int j = 0; j < m; j ++) {
                        modify(f[i][j]);
                        modify(f[i][j]-1);
                        if (ok(i,j)) modify(f[i][j]);
                }
        printf("%d\n",ans1+ans2);
        return 0;
}
