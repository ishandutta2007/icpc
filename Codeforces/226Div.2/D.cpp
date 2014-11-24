#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <math.h>
using namespace std;
const int N = 22;
int n;
const double eps = 1e-8,pi = atan(1.0)*4;
double l,r,x[N],y[N],a[N],dp[1<<20];
double move(double x,double y,double A) {
        double B = atan2(y,x);
        double C = pi-A-B;
        if (C<eps) return r;
        double c = sqrt(x*x+y*y);
        return c/sin(C)*sin(A);
}
int main() {
        scanf("%d%lf%lf",&n,&l,&r);
        r -= l;
        for (int i = 0; i < n; i ++) {
                scanf("%lf%lf%lf",x+i,y+i,a+i);
                x[i] -= l;
                a[i] *= pi/180;
        }
        int all = 1<<n;
        for (int s = 0; s < all; s ++) 
                for (int i = 0; i < n; i ++) if (!(s>>i&1)) {
                        double tmp = dp[s]+move(x[i]-dp[s],y[i],a[i]);
                        if (tmp>=r) {
                                printf("%.12f\n",r); return 0;
                        }
                        dp[s|1<<i] = max(dp[s|1<<i],tmp);
                }
        printf("%.12f\n",dp[all-1]);
        return 0;
}
