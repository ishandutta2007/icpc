#include <bits/stdc++.h>

int n,L,A,B,mod;

int work() {
    int ret = 0;
    A %= mod;
    B %= mod;
    int a = 0,b = L + 1;
    for (int i = 1,val = B; i <= n; ++ i) {
        val += A;
        if (val >= mod)
            val -= mod;
        if (val <= L / 2) {
            ret ++;
            if (a < val)
                a = val;
        } else if (val <= L) {
            if (b > val)
                b = val;
        }
    }
    return ret + (1ll * a + b <= L);
}

int main() {
    while (scanf("%d%d%d%d%d",&n,&L,&A,&B,&mod) == 5) {
        printf("%d\n",work());
    }
}
