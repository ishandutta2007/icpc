#include <bits/stdc++.h>

int main() {
    int cas;
    scanf("%d",&cas);
    while (cas--) {
        int n,m;
        scanf("%d%d",&n,&m);
        n --;
        int sa = 0,sb = 0,x;
        for (int i = 0; i < n; ++ i) {
            scanf("%d",&x);
            sa += x;
        }
        for (int i = 0; i < m; ++ i) {
            scanf("%d",&x);
            sb += x;
        }
        printf("%d %d\n",sb / m + 1,(sa + n - 1) / n - 1);
    }
}
