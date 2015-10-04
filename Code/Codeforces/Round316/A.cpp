#include <bits/stdc++.h>

int cnt[100 + 1];
int n,m;

int main() {
    scanf("%d%d",&n,&m);
    for (int i = 0; i < m; ++ i) {
        int A[n];
        int p = 0;
        for (int j = 0; j < n; ++ j) {
            scanf("%d",A + j);
            if (A[j] > A[p]) {
                p = j;
            }
        }
        cnt[p] ++;
    }
    int p = 0;
    for (int i = 0; i < n; ++ i) {
        if (cnt[i] > cnt[p]) {
            p = i;
        }
    }
    printf("%d\n",p + 1);
}
