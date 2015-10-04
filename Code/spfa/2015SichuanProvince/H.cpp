#include <stdio.h>
#include <string.h>
#include <algorithm>

const int N = 50 + 5;
int A[N],B[N],C[N];
int n,m1,m2;
bool graph[N][N];
int vis[N],tim;
int match[N];
bool ban[N];

bool expath(int u) {
    for (int v = 0; v < n; ++ v) {
        if (vis[v] != tim && graph[u][v] && !ban[v]) {
            vis[v] = tim;
            if (match[v] == -1 || expath(match[v])) {
                match[v] = u;
                return true;
            }
        }
    }
    return false;
}

bool work() {
    memset(graph,0,sizeof(graph));
    for (int i = 0; i < n; ++ i) {
        for (int j = 0; j < n; ++ j) {
            int low = 0,high = n - 1;
            for (int k = 0; k < m1; ++ k) {
                if (A[k] <= j && j <= B[k]) {
                    low = std::max(low,C[k]);
                }
            }
            for (int k = m1; k < m1 + m2; ++ k) {
                if (A[k] <= j && j <= B[k]) {
                    high = std::min(high,C[k]);
                }
            }
            if (i < low || i > high) continue;
            bool flag = true;
            for (int k = 0; k < m1 + m2; ++ k) {
                if (C[k] == i && (j < A[k] || B[k] < j)) {
                    flag = false;
                }
            }
            graph[j][i] = flag;
        }
   }
    memset(match,-1,sizeof(match));
    memset(ban,0,sizeof(ban));
    for (int t = 0; t < n; ++ t) {
        for (int i = n - 1; i >= t; -- i) {
            tim ++;
            if (!expath(i)) {
                return false;
            }
        }
        for (int i = 0; i < n; ++ i) {
            if (match[i] == t) {
                ban[i] = true;
            } else if (!ban[i]) {
                match[i] = -1;
            }
        }
    }
    int answer[N];
    for (int i = 0; i < n; ++ i) {
        answer[match[i]] = i;
    }
    for (int i = 0; i < n; ++ i) {
        if (i) putchar(' ');
        printf("%d",answer[i] + 1);
    }
    puts("");
    return true;
}

int main() {
    while (scanf("%d%d%d",&n,&m1,&m2) == 3) {
        for (int i = 0; i < m1 + m2; ++ i) {
            scanf("%d%d%d",A + i,B + i,C + i); A[i] --; B[i] --; C[i] --;
        }
        if (!work()) {
            puts("-1");
        }
    }
}
