#include <stdio.h>
#include <string.h>
#include <algorithm>
typedef long long LL;

const int N = 100000 + 5;
int n;
int A[N];
int B[N];

LL work() {
    LL ret = 0;
    for (int bit = 1,mod = 1; bit <= 9; ++ bit) {
        mod *= 10;
        for (int i = 0; i < n; ++ i) {
            B[i] = A[i] % mod;
        }
        std::sort(B,B + n);
        for (int i = 0,j = n - 1; i < n; ++ i) {
            while (j >= 0 && B[i] + B[j] >= mod) -- j;
            if (j < i) {
                ret += i - 1 - j;
            }
        }
    }
    return ret;
}

int main() {
    while (scanf("%d",&n) == 1) {
        for (int i = 0; i < n; ++ i) {
            scanf("%d",A + i);
        }
        printf("%lld\n",work());
    }
}
