#include <bits/stdc++.h>

char str[20 + 5];
int n;
bool graph[20][100];
int left[100];
bool vis[100];

bool expath(int u) {
    for (int v = 0; v < n; ++ v) {
        if (!vis[v] && graph[u][v]) {
            vis[v] = true;
            if (left[v] == - 1 || expath(left[v])) {
                left[v] = u;
                return true;
            }
        }
    }
    return false;
}

int main() {
    scanf("%s%d",str,&n);
    for (int i = 0; i < n; ++ i) {
        char s[2];
        for (int j = 0; j < 6; ++ j) {
            scanf("%s",s);
            for (int k = 0; str[k]; ++ k) {
                if (str[k] == s[0]) {
                    graph[k][i] = true;
                }
            }
        }
    }
    memset(left,-1,sizeof(left));
    for (int i = 0; str[i]; ++ i) {
        memset(vis,false,sizeof(vis));
        if (!expath(i)) {
            puts("NO");
            return 0;
        }
    }
    puts("YES");
}
