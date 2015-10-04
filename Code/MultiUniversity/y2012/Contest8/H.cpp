#include <bits/stdc++.h>

int n;
int answer[100000 + 5];

void work() {
    int t = n;
    for (int i = 1; i <= t; ++ i) {
        t = std::min(t,std::max(i,(n + i - 1) / i));
    }
    for (int i = 1; i <= n; ++ i)
        answer[i] = i;
    for (int i = 0,j = t; i < n; ) {
        int l = 1;
        while ((j - 1) * 1ll * t < n - i - l) ++ l;
        std::reverse(answer + i + 1,answer + i + l + 1);
        i += l;
        -- j;
    }
    for (int i = 1; i <= n; ++ i) {
        if (i != 1) putchar(' ');
        printf("%d",answer[i]);
    }
    puts("");
}

int main() {
    int cas;
    scanf("%d",&cas);
    while (cas--) {
        scanf("%d",&n);
        work();
    }
}
