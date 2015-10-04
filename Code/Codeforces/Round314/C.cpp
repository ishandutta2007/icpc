#include <bits/stdc++.h>
typedef long long LL;

const int N = 200000 + 5;
int n,K,A[N];
int tot;
std::map<int,int> map;
std::vector<int> vec[N];

LL work() {
    int zero = 0;
    for (int i = 0; i < n; ++ i) {
        if (A[i] == 0) {
            zero ++;
        } else {
            int cnt = 0;
            while (K != 1 && A[i] % K == 0) {
                A[i] /= K;
                cnt ++;
            }
            if (map.find(A[i]) == map.end()) {
                map[A[i]] = tot ++;
            }
            vec[map[A[i]]].push_back(cnt);
        }
    }
    LL ret = zero * 1ll * (zero - 1) * (zero - 2) / 6;
    for (int t = 0; t < tot; ++ t) {
        if (K == 1) {
            int x = vec[t].size();
            ret += x * 1ll * (x - 1) * (x - 2) / 6;
            continue;
        }
        std::map<int,LL> count[2];
        for (int x : vec[t]) {
            ret += count[1][x - 1];
            count[1][x] += count[0][x - 1];
            count[0][x] ++;
        }
    }
    return ret;
}

int main() {
    scanf("%d%d",&n,&K);
    for (int i = 0; i < n; ++ i) {
        scanf("%d",A + i);
    }
    printf("%I64d\n",work());
}
