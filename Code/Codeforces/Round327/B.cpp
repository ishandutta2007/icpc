#include <bits/stdc++.h>

double X,Y;
double V,T;
double vx,vy,wx,wy;

const double eps = 1e-8;

int dcmp(double x) {
    return x < -eps ? -1 : x > eps;
}

double sqr(double x) {
    return x * x;
}

int circle_point_relation(double x,double y,double r,double px,double py) {
    return dcmp(r * r - (sqr(x - px) + sqr(y - py)));
}

double work() {
    if (circle_point_relation(T * vx,T * vy,T * V,X,Y) >= 0) {
        double l = 0,r = T;
        for (int step = 500; step > 0; -- step) {
            double mid = (l + r) * .5;
            if (circle_point_relation(mid * vx,mid * vy,mid * V,X,Y) >= 0)
                r = mid;
            else
                l = mid;
        }
        return r;
    }
    double l = T,r = 1e8;
    for (int step = 500; step > 0; -- step) {
        double mid = (l + r) * .5;
        if (circle_point_relation(T * vx + (mid - T) * wx,
                    T * vy + (mid - T) * wy,mid * V,X,Y) >= 0)
            r = mid;
        else 
            l = mid;
    }
    return r;
}

int main() {
    {
        int a,b,c,d;
        scanf("%d%d%d%d",&a,&b,&c,&d);
        X = c - a;
        Y = d - b;
    }
    scanf("%lf%lf",&V,&T);
    scanf("%lf%lf%lf%lf",&vx,&vy,&wx,&wy);
    printf("%.15f\n",work());
}
