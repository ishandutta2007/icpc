#include <bits/stdc++.h>
using LL = long long ;

const int N = 10000 + 5;
int A[N],n;
int pre[N];
LL dp[N];
std::pair<int,int> B[N];

std::pair<int,LL> que[N];

LL cross(std::pair<int,LL> a,std::pair<int,LL> b,std::pair<int,LL> c) {
    return (a.first - c.first) * 1ll * (b.second - c.second)
        - (a.second - c.second) * 1ll * (b.first - c.first);
}

void work() {
    std::sort(B + 1,B + n + 1);
    for (int i = 1; i <= n; ++ i) {
        A[i] = B[i].first;
    }
    int qf = 0,qe = 0;
    que[qe++] = {0,0ll};
    for (int i = 1; i <= n; ++ i) {
        while (qf + 1 < qe && que[qf].second - que[qf].first * 1ll
                * A[i] >= que[qf + 1].second - que[qf + 1].first * 1ll
                * A[i]) 
            qf ++;
        pre[i] = que[qf].first;
        dp[i] = que[qf].second + (i - que[qf].first) * 1ll * A[i]
            + A[i] * 1ll * (n - i);
        auto t = std::make_pair(i,dp[i]);
        while (qf + 1 < qe && cross(t,que[qe - 1],que[qe - 2]) >= 0)
            qe --;
        que[qe++] = t;
    }
    printf("%I64d\n",dp[n]);
    std::vector<int> answer;
    for (int i = n; i > 0; i = pre[i]) {
        answer.push_back(i - pre[i]);
    }
    printf("%d\n",(int)answer.size());
    for (int i = (int)answer.size() - 1,j = 0; i >= 0; -- i) {
        printf("%d",answer[i]);
        for (int k = 1; k <= answer[i]; ++ k) {
            printf(" %d",B[j + k].second);
        }
        puts("");
        j += answer[i];
    }
}

int main() {
    freopen("iq.in","r",stdin);
    freopen("iq.out","w",stdout);
    while (scanf("%d",&n) == 1) {
        if (n == 0) break;
        for (int i = 1; i <= n; ++ i) {
            scanf("%d",A + i);
            B[i] = {A[i],i};
        }
        work();
    }
}
