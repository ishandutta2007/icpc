#include <bits/stdc++.h>

const int N = 200000 + 5;
int n,S[N];

double solve(double x) {
    double ret = 0.;
    double low = 0,high = 0;
    for (int i = 1; i <= n; ++ i) {
        ret = std::max(ret,std::abs(S[i] - x * i - low));
        ret = std::max(ret,std::abs(high - (S[i] - x * i)));
        low = std::min(low,S[i] - x * i);
        high = std::max(high,S[i] - x * i);
    }
    return ret;
}

double work() {
    double l = -10000,r = 10000;
    for (int step = 100; step > 0; -- step) {
        double lmid = (l * 2 + r) / 3;
        double rmid = (l + r * 2) / 3;
        if (solve(lmid) > solve(rmid)) {
            l = lmid;
        } else {
            r = rmid;
        }
    }
    return solve((l + r) / 2);
}

int main() {
    scanf("%d",&n);
    for (int i = 1; i <= n; ++ i) {
        scanf("%d",S + i);
        S[i] += S[i - 1];
    }
    printf("%.10f\n",work());
}
