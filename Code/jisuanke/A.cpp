#include <bits/stdc++.h>
typedef long long LL;

int X[2],Y[2],Z[2];
LL answer[8];
int tot;

void calc(int dx,int dy,int dz) {
    int x[2],y[2],z[2];
    x[0] = X[0];
    x[1] = X[1];
    y[0] = Y[0];
    y[1] = Y[1];
    z[0] = Z[0];
    z[1] = Z[1];
    for (int i = 0; i < 2; ++ i) {
        if (x[i] * dx < 0) x[i] = 0;
        if (y[i] * dy < 0) y[i] = 0;
        if (z[i] * dz < 0) z[i] = 0;
    }
    answer[tot++] = (x[1] - x[0]) * 1ll * (y[1] - y[0]) * (z[1] - z[0]);
}

void work() {
    tot = 0;
    calc(1,1,1);
    calc(-1,1,1);
    calc(-1,-1,1);
    calc(1,-1,1);
    calc(1,1,-1);
    calc(-1,1,-1);
    calc(-1,-1,-1);
    calc(1,-1,-1);
    for (int i = 0; i < tot; ++ i) {
        if (i) putchar(' ');
        printf("%lld",answer[i]);
    }
    puts("");
}

int main() {
    int cas;
    scanf("%d",&cas);
    while (cas--) {
        scanf("%d%d%d%d%d%d",X + 0,X + 1,Y + 0,Y + 1,Z + 0,Z + 1);
        work();
    }
}
