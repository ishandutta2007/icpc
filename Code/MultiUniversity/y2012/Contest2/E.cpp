#include <bits/stdc++.h>

const int INF = 0x3f3f3f3f;
std::pair<int,int> A[2000];
int n;
int h;
int dp[2000 + 1][2000 + 1];

inline void update(int &a,int b) {
    if (a > b) a = b;
}

int work() {
    std::sort(A,A + n);
    std::reverse(A,A + n);
    memset(dp,INF,sizeof(dp));
    dp[0][0] = 0;
    int sum = 0;
    for (int i = 0; i < n; ++ i) {
        int a = A[i].second;
        int b = A[i].first - a;
        sum += a;
        for (int j = 0; j <= i; ++ j) {
            if (dp[i][j] == INF) continue;
            update(dp[i + 1][j + 1],std::max(dp[i][j],h - sum - b));
            update(dp[i + 1][j],dp[i][j] - a);
        }
    }
    for (int i = n; i >= 0; -- i) {
        if (dp[n][i] <= 0)
            return i;
    }
}

int main() {
    while (scanf("%d",&n) == 1) {
        for (int i = 0; i < n; ++ i) {
            int a,b;
            scanf("%d%d",&a,&b);
            A[i] = {a + b,a};
        }
        scanf("%d",&h);
        printf("%d\n",work());
    }
}
