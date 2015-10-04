#include <bits/stdc++.h>

const int N = 50000 + 5;
int n;
int label[100],e[100][3];

int mlabel[N],me[N][3];
int m;

int vis[100][N],tim;

void copy() {
    for (int i = 0; i < n; ++ i) {
        mlabel[m + i] = (label[i] + 1) % 3;
        me[i + m][label[i]] = e[i][mlabel[m + i]] + m;
    }
}

void solve(int source) {
    int u = source,v = 0;
    tim ++;
    while (true) {
        if (vis[u][v] == tim) {
            return ;
        }
        vis[u][v] = tim;
        int &nv = me[v][label[u]];
        int nu = e[u][mlabel[v]];
        if (nv == -1) {
            copy();
            nv = nu + m;
            m += n;
            return ;
        }
        u = nu;
        v = nv;
    }
}

void work() {
    m = 1;
    for (int s = 0; s < n; ++ s) {
        solve(s);
    }
    for (int i = 0; i < m; ++ i) {
        for (int j = 0; j < 3; ++ j) {
            if (me[i][j] == -1) {
                me[i][j] = 0;
            }
        }
    }
}

int main() {
    freopen("epic.in","r",stdin);
    freopen("epic.out","w",stdout);
    memset(me,-1,sizeof(me));
    scanf("%d",&n);
    for (int i = 0; i < n; ++ i) {
        char str[2];
        scanf("%s%d%d%d",str,e[i] + 0,e[i] + 1,e[i] + 2);
        e[i][0] --;
        e[i][1] --;
        e[i][2] --;
        label[i] = str[0] == 'R' ? 0 : str[0] == 'P' ? 1 : 2;
    }
    work();
    printf("%d\n",m);
    for (int i = 0; i < m; ++ i) {
        printf("%c %d %d %d\n","RPS"[mlabel[i]],me[i][0] + 1,
                me[i][1] + 1,me[i][2] + 1);
    }
}
