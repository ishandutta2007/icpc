#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <string>
using namespace std;
const int INF = 0x3f3f3f3f,N = 1010;
int n,m;
int dir[4][2] = {1,0,0,1,-1,0,0,-1};
vector<string> s;
int f[N][N];
bool in[N][N];
int dfs(int x,int y) {
        if (in[x][y]) return INF;
        if (f[x][y]!=-1) return f[x][y];
        f[x][y] = 0;
        in[x][y] = true;
        for (int i = 0; i < 4; i ++) {
                int ex = x+dir[i][0];
                int ey = y+dir[i][1];
                if (ex<0 || ex>=n || ey<0 || ey>=m) continue;
                char a = s[x][y];
                char b = s[ex][ey];
                if (a=='D' && b=='I'
                 || a=='I' && b=='M'
                 || a=='M' && b=='A'
                 || a=='A' && b=='D')
                        f[x][y] = max(f[x][y],dfs(ex,ey));
        }
        in[x][y] = false;
        if (f[x][y]==INF) return INF;
        f[x][y] += s[x][y]=='A';
        return f[x][y];
}
int main() {
        cin >> n >> m;
        s.resize(n);
        for (int i = 0; i < n; i ++) cin >> s[i];
        int ans = 0;
        memset(f,-1,sizeof(f));
        for (int i = 0; i < n; i ++)
                for (int j = 0; j < m; j ++)
                        if (s[i][j]=='D')
                                ans = max(ans,dfs(i,j));
        if (ans==INF)
                cout << "Poor Inna!" << endl;
        else if (ans==0)
                cout << "Poor Dima!" << endl;
        else
                cout << ans << endl;
        return 0;
}
