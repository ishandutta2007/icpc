#include <bits/stdc++.h>

const int INF = 0x3f3f3f3f;
const int N = 1000 + 5;
int h,w,n;
char mat[N][N];
char buf[1000000 + 5];
int trans[1000000 + 5][4];
int dir[4][2] = {-1,0,0,1,1,0,0,-1};
int program[1000000 + 5];
int dis[N][N][4];

struct Node {
    int v;
    int x,y,d;

    bool operator < (const Node &rhs) const {
        return v > rhs.v;
    }
};

bool work() {
    program[0] = 0;
    for (int i = 0; i < n; ++ i) {
        if (buf[i] == 'L')
            program[i + 1] = (program[i] + 3) % 4;
        else
            program[i + 1] = (program[i] + 1) % 4;
    }
    for (int i = 0; i < 4; ++ i) {
        trans[n + 1][i] = INF;
    }
    for (int i = n; i >= 0; -- i) {
        for (int j = 0; j < 4; ++ j) {
            trans[i][j] = trans[i + 1][j];
        }
        trans[i][program[i]] = i;
    }
    std::priority_queue<Node> que;
    for (int i = 0; i < h; ++ i) {
        for (int j = 0; j < w; ++ j) {
            for (int d = 0; d < 4; ++ d) {
                dis[i][j][d] = INF;
            }
            if (mat[i][j] == 'S') {
                dis[i][j][0] = 0;
                que.push({0,i,j,0});
            }
        }
    }
    while (!que.empty()) {
        Node f = que.top(); que.pop();
        if (dis[f.x][f.y][f.d] != f.v) continue;
        if (mat[f.x][f.y] == 'E') return true;
        for (int i = 0; i < 4; ++ i) {
            if (trans[f.v][i] == INF) continue;
            if (dis[f.x][f.y][i] > trans[f.v][i]) {
                dis[f.x][f.y][i] = trans[f.v][i];
                que.push({dis[f.x][f.y][i],f.x,f.y,i});
            }
        }
        int ex = f.x + dir[f.d][0];
        int ey = f.y + dir[f.d][1];
        if (ex >= 0 && ex < h && ey >= 0 && ey < w && mat[ex][ey] != '#'
                && dis[ex][ey][f.d] > f.v) {
            dis[ex][ey][f.d] = f.v;
            que.push({f.v,ex,ey,f.d});
        }
    }
    return false;
}

int main() {
    while (scanf("%d%d%d",&h,&w,&n) == 3) {
        scanf("%s",buf);
        for (int i = 0; i < h; ++ i) {
            scanf("%s",mat[i]);
        }
        puts(work() ? "Yes" : "No");
    }
}
