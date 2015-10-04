#include <bits/stdc++.h>

using namespace std;

int c[11][11], b[11][11][11];

void init(int n) {
    c[0][0] = 1;
    for(int i = 1;i <= n; i++) {
        c[i][0] = 1;
        for(int j = 1;j <= n; j++) c[i][j]=c[i-1][j]+c[i-1][j-1];
    }
    memset(b, 0, sizeof(b));
    for(int i = 0;i <= n; i++) {
        for(int j = 0;j <= n; j++) {
            for(int k = 0;k <= j; k++) {
                if(k&1)
                    b[i][j][k+i] -= c[j][k];
                else
                    b[i][j][k+i] += c[j][k];
            }
        }
    }
}

int n, a[11], ans;

void dfs(int cr) {
    if(cr==0) {
        if(a[0] == 1)
            ans++;
        return ;
    }
//    printf("cr = %d\n", cr);
    for(int i = 0;i < 1<<cr+1; i++) {
        for(int j = 0;j <= cr; j++) if(i>>j&1) {
            for(int k = 0;k <= cr; k++)
                a[k] += b[j][cr-j][k];
        }
        if(a[0] <= 1 && a[cr] == 0) {
            dfs(cr-1);
        }
        for(int j = 0;j <= cr; j++) if(i>>j&1) {
            for(int k = 0;k <= cr; k++)
                a[k] -= b[j][cr-j][k];
        }
    }
}

int fk[] = {1,2,5,14,43,140,474,1648,5839};

int main() {
    freopen("immetric.in", "r", stdin);
    freopen("immetric.out", "w", stdout);
    init(9);
    int cas = 1;
    while(scanf("%d", &n) == 1 && n) {
        printf("Case #%d: %d\n", cas++, fk[n-1]);
    }
    return 0;
    while(scanf("%d", &n) == 1 && n) {
        for(int i = 0;i <= n; i++) {
            a[i] = 0;
        }
        ans = 0;
        dfs(n);
        printf("Case #%d: %d\n", cas++, ans);
    }
    return 0;
}
/*
1
Case #1: 1
2
Case #2: 3
3
Case #3: 8
4
Case #4: 22
5
Case #5: 65
*/
