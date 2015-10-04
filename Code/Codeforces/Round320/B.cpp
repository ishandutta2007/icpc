#include <bits/stdc++.h>
typedef long long LL;

const int N = 200000 + 5;
int A[N],n,K,x;
int L[N],R[N];

LL work() {
    LL ret = 0;
    for (int i = 1; i < n; ++ i) {
        L[i] = L[i - 1] | A[i - 1];
    }
    for (int i = n - 1; i >= 0; -- i) {
        R[i] = R[i + 1] | A[i];
    }
    for (int i = 0; i < n; ++ i) {
        LL t = A[i];
        for (int j = 0; j < K; ++ j) {
            t *= x;
        }
        ret = std::max(ret,L[i] | R[i + 1] | t);
    }
    return ret;
}

int main() {
    scanf("%d%d%d",&n,&K,&x);
    for (int i = 0; i < n; ++ i) {
        scanf("%d",A + i);
    }
    printf("%I64d\n",work());
}
