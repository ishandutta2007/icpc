#include <bits/stdc++.h>

int main() {
    int cas,ca = 0;
    scanf("%d",&cas);
    while (cas--) {
        int n,x;
        scanf("%d",&n);
        bool flag = true;
        for (int i = 0; i < n; ++ i) {
            scanf("%d",&x);
            flag &= x % 3 == 0;
        }
        printf("Case #%d: %s\n",++ca,flag ? "Yes" : "No");
    }
}
