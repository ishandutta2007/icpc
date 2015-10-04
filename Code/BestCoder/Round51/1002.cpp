#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <vector>

int k,b,x0,p;

int gcd(int a,int b) {
    return b == 0 ? a : gcd(b,a % b);
}

int work() {

    for (int i = 1,x = x0; i <= 100000; ++ i) {
        x = (k * 1ll * x + b) % p;
        if (x == x0)
            return i;
    }
    if (b == 0) {
        if (gcd(k,p) == 1)
            return p - 1;
    }
    return -1;
}

int main() {
    int cas;
    scanf("%d",&cas);
    while (cas--) {
        scanf("%d%d%d%d",&k,&b,&x0,&p);
        printf("%d\n",work());
    }
}

