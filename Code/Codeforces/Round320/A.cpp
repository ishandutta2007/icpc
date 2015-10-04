#include <bits/stdc++.h>
using LL = long long ;

const double Inf = 1e10;

int a,b;

double solve(int a,int b) {
    if (a < 0) return Inf;
    if (a == 0) return b;
    if (a < 2 * b) return Inf;
    return a * 1. / (a / (2 * b)) / 2;
}

bool work() {
    double ret = std::min(solve(a - b,b),solve(a + b,b));
    if (ret == Inf) return false;
    printf("%.10f\n",ret);
    return true;
}

int main() {
    scanf("%d%d",&a,&b);
    if (!work()) {
        puts("-1");
    }
}
