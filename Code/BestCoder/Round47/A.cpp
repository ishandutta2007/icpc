#include <stdio.h>
#include <algorithm>
#include <string.h>
#include <vector>
typedef long long LL;

const int N = 1000 + 5;
int n,A[N];
const LL Inf = 1e16;
int P;

LL solve() {
    LL ret = -Inf;
    LL sum = 0;
    for (int i = 0; i < n; ++ i) {
        ret = std::max(ret,1ll * A[i]);
        sum += A[i];
        ret = std::max(ret,sum);
        if (sum < 0) {
            sum = 0;
        }
    }
    return ret;
}

LL work() {
    LL ret = -Inf;
    for (int i = 0; i < n; ++ i) {
        int t = A[i];
        A[i] = P;
        ret = std::max(ret,solve());
        A[i] = t;
    }
    return ret;
}

int main() {
    int cas,ca = 0;
    scanf("%d",&cas);
    while (cas--) {
        scanf("%d%d",&n,&P);
        for (int i = 0; i < n; ++ i) {
            scanf("%d",A + i);
        }
        printf("%I64d\n",work());
    }
}
