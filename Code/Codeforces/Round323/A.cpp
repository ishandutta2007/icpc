#include <bits/stdc++.h>
typedef long long LL;

const int N = 500 + 1;
int n;
int A[N * N];
int B[N],tot;

int gcd(int a,int b) {
    return b == 0 ? a : gcd(b,a % b);
}

int main() {
    scanf("%d",&n);
    for (int i = 0; i < n * n; ++ i) {
        scanf("%d",A + i);
    }
    std::sort(A,A + n * n);
    std::multiset<int> mset;
    for (int i = n * n - 1; i >= 0; -- i) {
        int x = A[i];
        if (mset.find(x) != mset.end()) {
            mset.erase(mset.find(x));
            continue;
        }
        B[tot++] = x;
        for (int j = 0; j + 1 < tot; ++ j) {
            mset.insert(gcd(x,B[j]));
            mset.insert(gcd(x,B[j]));
        }
        printf("%d ",x);
    }
    puts("");
}

/**
 * don't hack me >_<
 */
