/* Created Time: Friday, November 22, 2013 PM03:19:25 CST */
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int N = 555555;
typedef long long lld;
int k,n;
int prim[N],ptot;
int a[N],p;
void work() {
    n = 2*k*k;
    a[p++] = 1;
    for (int it = 0; it < ptot; it ++) {
        lld c = prim[it];
        lld x;
        int d = p;
        for (int i = 0; i < d; i ++)
            if ((x=c*a[i])<=n) a[d++] = x;
        if (d-p>=k) {
            for (int i = 0; i < k; i ++)
                printf("%d ",a[d-1-i]);
            return ;
        }
        p = d;
    }
}
int main() {
    for (int i = 2; i < N; i ++) if (!prim[i]) {
        prim[ptot++] = i;
        for (int j = i+i; j < N; j += i) prim[j] = 1;
    }

    scanf("%d",&k);
    work();
    return 0;
}
