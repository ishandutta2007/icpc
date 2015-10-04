#include <stdio.h>
#include <algorithm>

int n,m,p,q;

int work() {
    if (p * m <= q) {
        return n * p;
    }
    int ret = n / m * q;
    n = n % m;
    return ret + std::min(p * n,q);
}


int main() {
    int cas;
    scanf("%d",&cas);
    while (cas--) {
        scanf("%d%d%d%d",&n,&m,&p,&q);
        printf("%d\n",work());
    }
}
