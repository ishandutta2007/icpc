#include <bits/stdc++.h>
typedef long long LL;

const int N = 200000 * 2 + 5;
int n,A[N];
std::vector<int> vec[N];
int mark[N],md;

int gcd(int a,int b) {
    return b == 0 ? a : gcd(b,a % b);
}

int cnt[N];

LL calc(int s) {
    md ++;
    for (int i = 0; i < s; ++ i) {
        int mx = -1;
        for (int p = i; ; ) {
            mx = std::max(A[p],mx);
            p = (p + s) % n;
            if (p == i) break;
        }
        for (int p = i; ; ) {
            if (A[p] == mx) {
                mark[p] = mark[p + n] = md;
            }
            p = (p + s) % n;
            if (p == i) break;
        }
    }
    memset(cnt,0,sizeof(cnt));
    for (int x : vec[s]) {
        cnt[x] ++;
    }
    for (int i = 1; i <= n; ++ i)
        cnt[i] += cnt[i - 1];
    LL ret = 0;
    for (int i = 0,j = 0; i < n; ++ i) {
        if (j < i) j = i;
        while (j < i + n - 1 && mark[j] == md) ++ j;
        ret += cnt[j - i];
    }
    return ret;
}

LL work() {
    for (int i = 1; i < n; ++ i) {
        vec[gcd(i,n)].push_back(i);
    }
    LL ret = 0;
    for (int s = 1; s < n; ++ s) {
        if (vec[s].empty()) continue;
        ret += calc(s);
    }
    return ret;
}

int main() {
    scanf("%d",&n);
    for (int i = 0; i < n; ++ i) {
        scanf("%d",A + i);
    }
    printf("%I64d\n",work());
}
