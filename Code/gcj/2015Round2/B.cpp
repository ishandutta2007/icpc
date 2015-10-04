#include <bits/stdc++.h>

int n;
double V,X;
double R[100],C[100];

bool check(double limit) {
    double now = 0;
    double vol = 0;
    for (int i = 0; i < n; ++ i) {
        vol += R[i] * limit;
        now += R[i] * limit * C[i];
    }
}

bool work() {
    for (int i = 0; i < n; ++ i) {
        C[i] -= X;
    }
    double l = 0,r = 1e20;
    bool ok = false;
    for (int step = 0; step <= 500; ++ step) {
        double mid = (l + r) * .5;
        if (check(mid)) {
            r = mid;
            ok = true;
        } else {
            l = mid;
        }
    }
    if (!ok) {
        return false;
    }
    printf("%.10f\n",r);
    return true;
}

int main() {
    int cas,ca = 0;
    scanf("%d",&cas);
    while (cas--) {
        printf("Case %d: ",++ca);
        scanf("%d%lf%lf",&n,&V,&X);
        for (int i = 0; i < n; ++ i) {
            scanf("%lf%lf",R + i,C + i);
        }
        if (!work()) {
            puts("IMPOSSIBLE");
        }
    }
}
