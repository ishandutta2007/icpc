#include <bits/stdc++.h>

int A[100];
int n,m;

bool work() {
    std::sort(A,A + m);
    for (int now = 1,s = 0; ; ++ now) {
        s += A[0];
        if (s > n)
            return now & 1;
    }
}

int main() {
    int cas;
    int ca = 0;
    scanf("%d",&cas);
    while (cas--) {
        scanf("%d%d",&n,&m);
        for (int i = 0; i < m; ++ i) {
            scanf("%d",A + i);
        }
        printf("Case #%d: %s\n",++ca,work() ? "Alice" : "Bob");
    }
}
