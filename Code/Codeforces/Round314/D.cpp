#include <bits/stdc++.h>

int n,k,a,m;

int calc(int n) {
    if (n < a) return 0;
    int l = 1,r = n;
    while (l <= r) {
        int mid = l + r >> 1;
        if (mid * 1ll * a + mid - 1 > n) {
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    return l - 1;
}

int main() {
    scanf("%d%d%d",&n,&k,&a);
    scanf("%d",&m);
    std::set<int> shooted;
    shooted.insert(0);
    shooted.insert(n + 1);
    int now = calc(n);
    for (int i = 0; i < m; ++ i) {
        int x;
        scanf("%d",&x);
        auto r = shooted.lower_bound(x);
        auto l = --shooted.lower_bound(x);
        now -= calc((*r - 1) - (*l + 1) + 1);
        shooted.insert(x);
        now += calc((*r - 1) - x);
        now += calc(x - 1 - (*l + 1) + 1);
        if (now < k) {
            printf("%d\n",i + 1);
            return 0;
        }
    }
    puts("-1");
}
