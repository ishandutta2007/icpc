#include <bits/stdc++.h>

int main() {
    int n,m,K;
    while (scanf("%d%d%d",&n,&m,&K) == 3) {
        std::set<std::pair<int,int>> set;
        for (int i = 0; i < m; ++ i) {
            int a,b;
            scanf("%d%d",&a,&b); a ++; b ++;
            if (a > n / 2) a = n + 1 - a;
            if (b > n / 2) b = n + 1 - b;
            if (a > b) std::swap(a,b);
            set.insert({a,b});
        }
        if (n & 1) n ++;
        int ret = 1;
        for (int i = (n / 2) * (n / 2 + 1) / 2 - set.size(); i > 0; i >>= 1) {
            if (i & 1) ret = ret * 1ll * K % 100000007;
            K = K * 1ll * K % 100000007;
        }
        printf("%d\n",ret);
    }
}
