#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <set>
typedef long long LL;

const int N = 100000 + 5;
int n,A[N];
int K;

LL work() {
    std::multiset<int> mset;
    LL ret = 0;
    for (int i = 0,j = 0; i < n; ++ i) {
        mset.insert(A[i]);
        while (std::abs(*mset.rbegin() - A[i]) >= K
                || std::abs(*mset.begin() - A[i]) >= K) {
            mset.erase(mset.find(A[j++]));
        }
        ret += i - j + 1;
    }
    return ret;
}

int main() {
    int cas;
    scanf("%d",&cas);
    while (cas--) {
        scanf("%d%d",&n,&K);
        for (int i = 0; i < n; ++ i) {
            scanf("%d",A + i);
        }
        printf("%I64d\n",work());
    }
}
