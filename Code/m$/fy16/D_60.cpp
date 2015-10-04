#include <bits/stdc++.h>

int dp[2000 + 1][100];
int A[100][100];
int n,m;

inline void update(int &a,int b) {
    if (a < b) a = b;
}

int deg[100];
int que[100];

int work() {
    if (m > 2000) return -1;

    for (int i = 0; i < n; ++ i) {
        for (int j = 0; j < n; ++ j) {
            if (A[i][j] != 0 || i == j) continue;
            deg[j] ++;
        }
    }
    int qf = 0,qe = 0;
    for (int i = 0; i < n; ++ i) {
        if (deg[i] == 0) 
            que[qe++] = i;
    }
    while (qf != qe) {
        int u = que[qf++];
        for (int v = 0; v < n; ++ v) {
            if (u == v || A[u][v] != 0) continue;
            if (--deg[v] == 0) 
                que[qe++] = v;
        }
    }
    if (qe != n) while (true);

    for (int i = 0; i <= m; ++ i) {
        for (int I = 0; I < n; ++ I) {
            int u = que[I];
            for (int v = 0; v < n; ++ v) {
                if (u != v && A[u][v] == 0) {
                    update(dp[i][v],dp[i][u] + 1);
                }
            }
        }
        for (int j = 0; j < n; ++ j) {
            for (int k = 0; k < n; ++ k) {
                if (A[j][k] == 0 || j == k) continue;
                if (i + A[j][k] <= m) {
                    update(dp[i + A[j][k]][k],dp[i][j] + 1);
                }
            }
        }
    }
    int ret = 0;
    for (int i = 0; i <= m; ++ i) {
        for (int j = 0; j < n; ++ j)
            update(ret,dp[i][j]);
    }
    return ret;
}

int main() {
    scanf("%d%d",&n,&m);
    for (int i = 0; i < n; ++ i) {
        for (int j = 0; j < n; ++ j) {
            scanf("%d",&A[i][j]);
        }
    }
    printf("%d\n",work());
}
