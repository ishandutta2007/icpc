#include <bits/stdc++.h>

using namespace std;

int main() {
    freopen("jubilee.in", "r", stdin);
    freopen("jubilee.out", "w", stdout);
    int n;
    while(scanf("%d", &n) == 1 && n) {
        if(n == 3) {
            printf("1\n");
            for(int i = 1;i <= 3; i++) printf("%d ", 1); puts("");
            for(int i = 1;i <= 3; i++) printf("%d ", 1); puts("");
        } else if(n <= 6) {
            printf("%d\n", 2);
            for(int i = 1;i <= n; i++) printf("%d ", i%2 ? 1 : 2); puts("");
            for(int i = 1;i <= n; i++) printf("%d ", i%2 ? 1 : 2); puts("");
        } else {
            printf("%d\n", 3);
            for(int i = 1;i <= n; i++) printf("%d ", i%3+1); puts("");
            for(int i = 1;i <= n; i++) printf("%d ", (i+2)%3+1); puts("");
        }
    }
    return 0;
}
