#include <bits/stdc++.h>

int n,A[15];
int dp[1 << 15];

inline void update(int &a,int b) {
    if (a < b) a = b;
}

int work() {
    std::sort(A,A + n);
    for (int mask = 0; mask < 1 << n; ++ mask) {
        for (int i = 0; i < n; ++ i) if (~mask >> i & 1) {
            for (int j = i + 1; j < n; ++ j) if (~mask >> j & 1) {
                for (int k = j + 1; k < n; ++ k) if (~mask >> k & 1) {
                    if (A[i] + A[j] <= A[k]) continue;
                    update(dp[mask ^ 1 << i ^ 1 << j ^ 1 << k],
                            dp[mask] + 1);
                }
            }
        }
    }
    return dp[(1 << n) - 1];
}

int main() {
    scanf("%d",&n);
    for (int i = 0; i < n; ++ i)
        scanf("%d",A + i);
    printf("%d\n",work());
}
