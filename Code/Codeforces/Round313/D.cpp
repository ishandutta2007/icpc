#include <bits/stdc++.h>

const int N = 100000 + 5;
int n,X[N],Y[N];

int gcd(int a,int b) {
    return b == 0 ? a : gcd(b,a % b);
}

double work() {
    long double ret = 0;
    long double add = 1;
    for (int i = 0; i < n; ++ i) {
        add *= 2;
    }
    add -= 1 + n + n * .5 * (n -1);
    add = 1 / add;
    for (int j = 1; j < n - 1; ++ j) {
        long double prob = 1. / (pow(2,j + 1) - (1 + n + n * .5 * (n - 1)) / pow(2,n - j - 1)) - add;
        for (int i = 0; i < n; ++ i) {
            int k = (i + j) % n;
            ret += prob * (X[i] * 1. * Y[k] - Y[i] * 1. * X[k] - gcd(std::abs(X[i] - X[k]),std::abs(Y[i] - Y[k])));
        }
        if (clock() >= 2.4 * CLOCKS_PER_SEC) break;
    }
    return ret * .5 + 1;
}

int main() {
    scanf("%d",&n);
    for (int i = 0; i < n; ++ i) {
        scanf("%d%d",X + i,Y + i);
    }
    printf("%.10f\n",work());
}
