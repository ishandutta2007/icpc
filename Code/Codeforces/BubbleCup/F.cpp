#include <bits/stdc++.h>
typedef long long LL;

const LL Inf = 1e16;
LL dp[10001];
int pos[10001],tot;
int L[5000],R[5000];
int n,x;

LL work() {
    std::sort(pos,pos + tot);
    tot = std::unique(pos,pos + tot) - pos;
    for (int i = 0; i < tot; ++ i) {
        dp[i] = pos[i] == x ? 0 : Inf;
    }
    for (int i = 0; i < n; ++ i) {
        LL val = Inf;
        for (int j = 0; j < tot && pos[j] <= L[i]; ++ j) {
            dp[j] += L[i] - pos[j];
            val = dp[j] = std::min(val,dp[j]);
        }
        val = Inf;
        for (int j = tot - 1; j >= 0 && pos[j] >= R[i]; -- j) {
            dp[j] += pos[j] - R[i];
            val = dp[j] = std::min(val,dp[j]);
        }
    }
    return *std::min_element(dp,dp + tot);
}

int main() {
    scanf("%d%d",&n,&x);
    pos[tot++] = x;
    for (int i = 0; i < n; ++ i) {
        scanf("%d%d",L + i,R + i);
        pos[tot++] = L[i];
        pos[tot++] = R[i];
    }
    printf("%I64d\n",work());
}
