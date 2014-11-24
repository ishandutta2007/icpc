#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
#include <vector>
#include <queue>
#include <cstdio>
using namespace std;
int n,m,val[10],tot,dis[22][22][(1<<8)+10];
int dir[4][2] = {1,0,0,1,-1,0,0,-1};
vector<string> s;
struct point {
        int x,y,st;
        point(int x = 0, int y = 0, int st = 0) : x(x),y(y),st(st){}
}ug[10];
bool cmp(point a,point b) {
        return s[a.x][a.y]<s[b.x][b.y];
}
int move(int x,int y,int d) {
        if (d==0 || d==2) return 0;
        if (d==1) y ++;
        int ret = 0;
        for (int i = 0; i < tot; i ++) {
                if (y==ug[i].y && x>ug[i].x) ret ^= 1<<i;
        }
        return ret;
}
int work() {
        int bx,by;
        for (int i = 0; i < n; i ++)
                for (int j = 0; j < m; j ++)
                        if (s[i][j]=='S') bx = i,by = j;
        s[bx][by] = '.';
        queue<point> que;
        que.push(point(bx,by,0));
        while (!que.empty()) {
                point f = que.front(); que.pop();
                for (int i = 0; i < 4; i ++) {
                        point e;
                        e.x = f.x+dir[i][0];
                        e.y = f.y+dir[i][1];
                        if (e.x<0 || e.x>=n || e.y<0 || e.y>=m || s[e.x][e.y]!='.') continue;
                        e.st = f.st^move(f.x,f.y,i);
                        if (!dis[e.x][e.y][e.st]) {
                                dis[e.x][e.y][e.st] = dis[f.x][f.y][f.st]+1;
                                que.push(e);
                        }
                }
        }

        int ret = 0;
        for (int st = 0; st < 1<<tot; st ++) {
                if (!dis[bx][by][st]) continue;
                int sum = 0;
                for (int i = 0; i < tot; i ++) 
                        if (st>>i&1) sum += val[i];
                ret = max(ret,sum-dis[bx][by][st]);
        }
        return ret;
}
int main() {
        cin >> n >> m;
        s.resize(n);
        for (int i = 0; i < n; i ++) {
                cin >> s[i];
                for (int j = 0; j < m; j ++) {
                        if (s[i][j]>='0' && s[i][j]<='9' || s[i][j]=='B') ug[tot++] = point(i,j);
                }
        }
        sort(ug,ug+tot,cmp);
        for (int i = 0; i < tot; i ++) val[i] = -555555;
        for (int i = 0; s[ug[i].x][ug[i].y]!='B' && i<tot; i ++) cin >> val[i];
        cout << work() << endl;
        return 0;
}
