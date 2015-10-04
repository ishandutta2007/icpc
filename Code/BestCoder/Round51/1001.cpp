#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <vector>
typedef long long LL;

inline void read(int &x) {
    char c;
    for (c = getchar(); c < '0' || c > '9'; c = getchar());
    for (x = 0; c >= '0' && c <= '9'; c = getchar()) x = x * 10 + c - '0';
}

const LL N = 3000000 + 5;
int n,A[N];
bool vis[N];
int count[N];

const LL MOD = 3221225473;

LL work() {
    for (int i = 1; i <= n; ++ i) {
        count[i] = 0;
        vis[i] = false;
    }
    for (int i = 1; i <= n; ++ i) {
        if (vis[i]) continue;
        int cnt = 0;
        while (!vis[i]) {
            vis[i] = true;
            i = A[i];
            cnt ++;
        }
        for (int j = 2; j <= cnt; ++ j) {
            if (cnt % j) continue;
            int t = 0;
            while (cnt % j == 0) {
                t ++;
                cnt /= j;
            }
            count[j] = std::max(count[j],t);
        }
    }
    LL ret = 1;
    for (int i = 2; i <= n; ++ i) {
        for (int j = 0; j < count[i]; ++ j) {
            ret = ret * i % MOD;
        }
    }
    return ret;
}

int main() {
    int cas;
    read(cas);
    while (cas--) {
        read(n);
        for (int i = 1; i <= n; ++ i) {
            read(A[i]);
        }
        printf("%I64d\n",work());
    }
}

