#include <stdio.h>
#include <string.h>
#include <algorithm>
typedef long long LL;

int n,m;
const int N = 100000 + 5;
int A[N],B[N];

LL work() {
    std::sort(A,A + n);
    std::sort(B,B + m);
    std::reverse(A,A + n);
    LL ret = 0;
    LL sum = 0;
    for (int i = 0; i < n && i < m; ++ i) {
        if (A[i] < B[i]) break;
        sum += A[i] - B[i];
        ret = std::max(ret,sum);
    }
    return ret;
}

int main() {
    int cas,ca = 0;
    scanf("%d",&cas);
    while (cas--) {
        scanf("%d%d",&n,&m);
        for (int i = 0; i < n; ++ i) {
            scanf("%d",A + i);
        }
        for (int i = 0; i < m; ++ i) {
            scanf("%d",B + i);
        }
        printf("%I64d\n",work());
    }
}
