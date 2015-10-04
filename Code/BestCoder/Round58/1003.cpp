#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <vector>
typedef long long LL;

const int N = 100000 + 5;
int n,m;
int A[N];

int a[N],b[N],c[N],d[N];

void modify(int *C,int p,int x) {
    for (int i = p; i < N; i += i & -i) C[i] += x;
}

int query(int *C,int p) {
    int ret = 0;
    for (int i = p; i > 0; i -= i & -i) ret += C[i];
    return ret;
}

LL work() {
    memset(a,0,sizeof(a));
    memset(b,0,sizeof(b));
    memset(c,0,sizeof(c));
    memset(d,0,sizeof(d));

    LL now = 0;

    for (int i = n; i > m; -- i) {
        now += query(d,A[i] - 1);
        modify(d,A[i],1);
    }

    LL best = now;

    for (int i = 1; i + m - 1 <= n; ++ i) {
        best = std::min(best,now);

        if (i + m > n) break;

        now += query(c,n) - query(c,A[i]) + query(d,A[i] - 1);
        modify(c,A[i],1);

        now -= query(c,n) - query(c,A[i + m]) + query(d,A[i + m] - 1);
        modify(d,A[i + m],-1);
    }

    return best;
}

int main() {
    int cas;
    scanf("%d",&cas);
    while (cas--) {
        scanf("%d%d",&n,&m);
        for (int i = 1; i <= n; ++ i) {
            scanf("%d",A + i);
        }
        printf("%I64d\n",work());
    }
}
