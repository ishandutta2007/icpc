#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <vector>

const int N = 100000 + 5;
const int MOD = (int)1e9 + 7;

int n,A[N];
int two[N];
int cnt[N];

struct O : std::vector<int> {
    void build() {
        std::sort(begin(),end());
        erase(std::unique(begin(),end()),end());
    }

    int get(int x) {
        return std::lower_bound(begin(),end(),x) - begin();
    }
} ss;

int work() {
    ss.clear();
    ss.push_back(0);
    for (int i = 1; i <= n; ++ i) {
        ss.push_back(A[i]);
        cnt[i] = 0;
    }
    ss.build();
    int ret = 0;
    for (int i = 1; i <= n; ++ i) {
        int x = ss.get(A[i]);
        ret += (A[i] * 1ll * two[n - 1] % MOD + MOD - cnt[x]
                * 1ll * two[n - i] % MOD) % MOD;
        ret %= MOD;
        cnt[x] += A[i] * 1ll * two[i - 1] % MOD;
        cnt[x] %= MOD;
    }
    return ret;
}

int main() {
    two[0] = 1;
    for (int i = 1; i < N; ++ i)
        two[i] = (two[i - 1] << 1) % MOD;
    int cas;
    scanf("%d",&cas);
    while (cas--) {
        scanf("%d",&n);
        for (int i = 1; i <= n; ++ i) {
            scanf("%d",A + i);
        }
        printf("%d\n",work());
    }
}
