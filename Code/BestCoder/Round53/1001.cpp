#include <stdio.h>
#include <string.h>
#include <algorithm>

int main() {
    int n,m;
    while (scanf("%d%d",&n,&m) == 2) {
        int cnt = 0;
        for (int i = 0; i < m; ++ i) {
            int a,b;
            scanf("%d%d",&a,&b);
            if (a > b) std::swap(a,b);
            if (a == 1 && b == n) cnt ++;
        }
        if (cnt == 0) {
            printf("1 1\n");
        } else {
            printf("1 %d\n",n * (n - 1) / 2);
        }
    }
}
