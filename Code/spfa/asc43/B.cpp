#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
typedef __int64 lld;
const int N = 1e5 + 5;
const lld INF = (1LL<<62) - 1;

inline void add(lld &x, lld ad) {
    if (x >= INF - ad) {
        x = INF + 1;
    }else {
        x += ad;
    }
}

int n;
lld k, sum;
lld dp[N];
int ans[N];

void work() {
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            if (dp[n - i - j] >= k) {
                for (int c = 0; c <= j; c++) {
                    ans[i + c] = (c == 0 ? i + j : i + c - 1);
                }
                i += j;
                break;
            }else {
                k -= dp[n - i - j]; 
            }
        }
    }
    for (int i = 1; i <= n; i++) printf("%d%c", ans[i], " \n"[i == n]);
    return ;
}

int main() {
    freopen("bubble.in", "r", stdin);
    freopen("bubble.out", "w", stdout);
    dp[0] = 1, sum = 1;
    for (int i = 1; i <= 1e5; i++) {
        dp[i] = sum;
        add(sum, dp[i]);
    }
    while (scanf("%d%I64d", &n, &k) == 2 && !(n == 0 && k == 0)) {
        work();
    }
    return 0;
}
