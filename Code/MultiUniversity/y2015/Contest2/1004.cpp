#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

typedef __int64 lld;

const int N = 1e5 + 5;

int L, n, k;
int x[N], a[N];
lld sumA[N], sumB[N];
int A[N], B[N];

void work() {
    int l = 0, r = 0;
    scanf("%d%d%d", &L, &n, &k);
    for (int i = 1; i <= n; i++) {
        scanf("%d%d", &x[i], &a[i]);
        if (x[i] <= L-x[i]) {
            for (int j = 1; j <= a[i]; j++) {
                A[++ l] = x[i] * 2;
            }
        }else {
            for (int j = 1; j <= a[i]; j++) {
                B[++ r] = (L - x[i]) * 2;
            } 
        }
    }
    fill(sumA, sumA + k, 0);
    fill(sumB, sumB + k, 0);
    sort(A + 1, A + 1 + l);
    sort(B + 1, B + 1 + r);
    for (int i = 1; i <= l; i++) {
        sumA[i % k] += A[i];
    }
    for (int i = 1; i <= r; i++) {
        sumB[i % k] += B[i];
    }
    lld ans = sumA[l % k] + sumB[r % k];
    for (int i = 0; i <= l; i++) {
        lld del = (l - i) / k + ((l - i) % k != 0);
        lld rem = (r - (del * k - (l - i)));
        lld add;
        if (i == 0) {
            add = 0;
        }else {
            add = sumA[i % k];
        }
        if (rem > 0) {
            ans = min(ans, add + sumB[rem % k] + del * L);
        }else {
            ans = min(ans, add + del * L);
        }
    }
    printf("%I64d\n", ans);
}

int main() {
    int T;
    scanf("%d", &T);
    for (int cas = 1; cas <= T; cas++) {
        work();
    }
    return 0;
}
