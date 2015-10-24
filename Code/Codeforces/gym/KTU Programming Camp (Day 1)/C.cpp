#include <bits/stdc++.h>

bool vis[25][25][25][25];
char str[25][26];
int n,m;
int dir[4][2] = {1,0,0,1,-1,0,0,-1};

int work() {
    int ax,ay,bx,by;
    for (int i = 0; i < n; ++ i) {
        for (int j = 0; j < m; ++ j) {
            if (str[i][j] == 'A') {
                ax = i;
                ay = j;
                str[i][j] = '.';
            } else if (str[i][j] == 'G') {
                bx = i;
                by = j;
                str[i][j] = '.';
            }
        }
    }
    std::queue<int> que[2];
    int cur = 0;
    que[cur].push(ax);
    que[cur].push(ay);
    que[cur].push(bx);
    que[cur].push(by);
    vis[ax][ay][bx][by] = true;
    int step = 0;
    while (true) {
        if (que[cur].empty()) {
            if (que[cur ^ 1].empty())
                return -1;
            cur ^= 1;
            step ++;
        }
        ax = que[cur].front(); que[cur].pop();
        ay = que[cur].front(); que[cur].pop();
        bx = que[cur].front(); que[cur].pop();
        by = que[cur].front(); que[cur].pop();
        if (str[ax][ay] == 'P') {
            return step;
        }
        for (int i = 0; i < 4; ++ i) {
            int tx = ax + dir[i][0];
            int ty = ay + dir[i][1];
            if (tx < 0 || tx >= n || ty < 0 || ty >= m) continue;
            if (str[tx][ty] == 'X') continue;
            int rx = bx,ry = by;
            if (ty < ry) {
                ry --;
            } else if (ty > ry) {
                ry ++;
            }
            if (str[rx][ry] == 'X' || ty == by) {
                rx = bx;
                ry = by;
                if (tx < rx) {
                    rx --;
                } else if (tx > rx) {
                    rx ++;
                }
                if (str[rx][ry] == 'X') {
                    rx = bx;
                    ry = by;
                }
            }
            if (vis[tx][ty][rx][ry]) continue;
            if (tx == rx && ty == ry) continue;
            vis[tx][ty][rx][ry] = true;
            que[cur ^ 1].push(tx);
            que[cur ^ 1].push(ty);
            que[cur ^ 1].push(rx);
            que[cur ^ 1].push(ry);
        }
    }
}

int main() {
    scanf("%d%d",&n,&m);
    for (int i = 0; i < n; ++ i) {
        scanf("%s",str[i]);
    }
    printf("%d\n",work());
}
