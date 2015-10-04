#include <stdio.h>
#include <string.h>
#include <algorithm>

char str[100 + 5];

const char aim[] = "anniversary";
int next[100],m;

bool work() {
    int n = strlen(str);
    for (int i = 0; i < n; ++ i) {
        for (int j = i + 1; j < n; ++ j) {
            int p = -1;
            int mx = -1;
            for (int k = 0; k <= i; ++ k) {
                while (p != -1 && str[k] != aim[p + 1]) p = next[p];
                if (str[k] == aim[p + 1]) {
                    p ++;
                    mx = std::max(mx,p);
                    if (p == m - 1) {
                        return true;
                    }
                }
            }
            p = mx;
            for (int k = i + 1; k <= j; ++ k) {
                while (p != -1 && str[k] != aim[p + 1]) p = next[p];
                if (str[k] == aim[p + 1]) {
                    p ++;
                    mx = std::max(mx,p);
                    if (p == m - 1) {
                        return true;
                    }
                }
            }
            p = mx;
            for (int k = j + 1; k < n; ++ k) {
                while (p != -1 && str[k] != aim[p + 1]) p = next[p];
                if (str[k] == aim[p + 1]) {
                    p ++;
                    mx = std::max(mx,p);
                    if (p == m - 1) {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

void init() {
    m = strlen(aim);
    next[0] = -1;
    for (int i = 1,j = -1; i < m; ++ i) {
        while (j != -1 && aim[j + 1] != aim[i]) j = next[j];
        next[i] = aim[j + 1] == aim[i] ? ++ j : -1;
    }
}

int main() {
    init();
    int cas;
    scanf("%d",&cas);
    while (cas--) {
        scanf("%s",str);
        puts(work() ? "YES" : "NO");
    }
}
