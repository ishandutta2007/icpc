#include <bits/stdc++.h>
typedef long long LL;

const int MOD = (int)1e9 + 9;
std::vector<int> L[7],R[7];
int n,p;
int len;

void decompose(LL x,std::vector<int> &A) {
    A.clear();
    while (x) {
        A.push_back(x % p);
        x /= p;
    }
    len = std::max<int>(len,A.size());
}

int dp[2][1 << 14][20];
int ways[1 << 14];

inline void add(int &a,int b) {
     a += b;
     if (a >= MOD) a -= MOD;
}

void show(int mask) {
    for (int i = 0; i < n + n; ++ i) {
        printf("%d",mask >> i & 1);
    }
    puts("");
}

int work() {
    memset(ways,0,sizeof(ways));
    ways[(1 << n + n) - 1] = 1;
    memset(dp,0,sizeof(dp));
    for (int at = len - 1; at >= 0; -- at) {
        int cur = 0,nex = 1;
        for (int mask = 0; mask < 1 << n + n; ++ mask) {
            dp[0][mask][0] = ways[mask];
        }
        for (int i = 0; i < n; ++ i) {
            for (int mask = 0; mask < 1 << n + n; ++ mask) {
                for (int sum = 0; sum < p; ++ sum) {
                    if (dp[cur][mask][sum] == 0) continue;
                    for (int val = 0; val + sum < p; ++ val) {
                        if ((mask >> i + i & 1) && val < L[i][at]) continue;
                        if ((mask >> i + i & 2) && val > R[i][at]) continue;
                        int nmask = ~(~mask | ((val != L[i][at]) << i + i)
                            | ((val != R[i][at]) << i + i + 1));
                        add(dp[nex][nmask][sum + val],dp[cur][mask][sum]);
                    }
                    dp[cur][mask][sum] = 0;
                }
            }
            std::swap(cur,nex);
        }
        for (int mask = 0; mask < 1 << n + n; ++ mask) {
            ways[mask] = 0;
            for (int sum = 0; sum < p; ++ sum) {
                add(ways[mask],dp[cur][mask][sum]);
                dp[cur][mask][sum] = 0;
            }
        }
    }
    int ret = 0;
    for (int mask = 0; mask < 1 << n + n; ++ mask) {
        add(ret,ways[mask]);
    }
    return ret;
}

int main() {
    int cas,ca = 0;
    scanf("%d",&cas);
    while (cas--) {
        scanf("%d%d",&n,&p);
        len = 1;
        for (int i = 0; i < n; ++ i) {
            LL x;
            scanf("%lld",&x);
            decompose(x,L[i]);
        }
        for (int i = 0; i < n; ++ i) {
            LL x;
            scanf("%lld",&x);
            decompose(x,R[i]);
        }
        for (int i = 0; i < n; ++ i) {
            L[i].resize(len);
            R[i].resize(len);
        }
        printf("Case %d: %d\n",++ca,work());
    }
}
