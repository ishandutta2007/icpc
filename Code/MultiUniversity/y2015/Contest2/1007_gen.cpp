#include <bits/stdc++.h>

int main() {
    freopen("1007.in","w",stdout);
    int cas = 1;
    printf("%d\n",cas);
    while (cas--) {
        int n = 100000,m = 100000;
        printf("%d %d\n",n,m);
        for (int i = 0; i < n; ++ i) {
            if (i) putchar(' ');
            printf("%d",1000000000);
        }
        puts("");
        printf("0 1 100000 %d\n",(int)1e9 - 1);
        m --;
        for (int i = 1; i <= n; i += 2) {
            printf("0 %d %d %d\n",i,i,0);
            m --;
        }
        for (int i = 0; i < m; ++ i) {
            printf("0 1 100000 %d\n",(int)1e9 - i - 10);
        }
    }
}
