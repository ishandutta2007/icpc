#include <bits/stdc++.h>

const int N = 200000 + 5;
int n,m;
std::pair<int,int> events[N],queries[N];
int answer[N];

int main() {
    int cas,ca = 0;
    scanf("%d",&cas);
    while (cas--) {
        scanf("%d%d",&n,&m);
        int tot = 0;
        for (int i = 0; i < n; ++ i) {
            int a,b;
            scanf("%d%d",&a,&b);
            events[tot++] = std::make_pair(a,1);
            events[tot++] = std::make_pair(b + 1,-1);
        }
        std::sort(events,events + tot);
        for (int i = 0; i < m; ++ i) {
            int t;
            scanf("%d",&t);
            queries[i] = std::make_pair(t,i);
        }
        std::sort(queries,queries + m);
        for (int i = 0,j = 0,cnt = 0; i < m; ++ i) {
            while (j < tot && events[j].first <= queries[i].first) {
                cnt += events[j].second;
                ++ j;
            }
            answer[queries[i].second] = cnt;
        }
        printf("Case #%d:\n",++ca);
        for (int i = 0; i < m; ++ i) {
            printf("%d\n",answer[i]);
        }
    }
}
