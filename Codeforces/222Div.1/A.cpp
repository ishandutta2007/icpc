#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
#include <vector>
using namespace std;
int dir[4][2] = {1,0,0,1,-1,0,0,-1};
int n,m,K;
struct point {int x,y;};
point que[300010];
int qf,qe;
bool vis[555][555];
vector<string> s;
void work() {
        qf = 0,qe = -1;
        int bx,by;
        for (int i = 0; i < n; i ++)
                for (int j = 0; j < m; j ++)
                        if (s[i][j]=='.') bx = i,by = j;
        que[++qe] = (point) {bx,by};
        vis[bx][by] = true;
        while (qf<=qe) {
                point f = que[qf++];
                for (int i = 0; i < 4; i ++) {
                        point e;
                        e.x = f.x+dir[i][0];
                        e.y = f.y+dir[i][1];
                        if (e.x<0 || e.x>=n || e.y<0 || e.y>=m || vis[e.x][e.y] || s[e.x][e.y]=='#') continue;
                        vis[e.x][e.y] = true;
                        que[++qe] = e;
                }
        }
        for (int i = 0; i < K; i ++) {
                point c = que[qe--];
                s[c.x][c.y] = 'X';
        }
} 
int main() {
        ios::sync_with_stdio(false);
        cin >> n >> m >> K;
        s.resize(n);
        for (int i = 0; i < n; i ++) cin >> s[i];
        work();
        for (int i = 0; i < n; i ++) cout << s[i] << endl;
        return 0;
}
