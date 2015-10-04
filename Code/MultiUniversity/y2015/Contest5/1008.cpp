#include <bits/stdc++.h>
typedef long long LL;

int main() {
    int cas;
    scanf("%d",&cas);
    while (cas--) {
        int n;
        scanf("%d",&n);
        std::priority_queue<int,std::vector<int>,
            std::greater<int>> que;
        for (int i = 0; i < n; ++ i) {
            int x;
            scanf("%d",&x);
            que.push(x);
        }
        LL answer = 0;
        while (!que.empty()) {
            int a = que.top(); que.pop();
            if (que.empty()) {
                break;
            }
            int b = que.top(); que.pop();
            answer += a + b;
            que.push(a + b);
        }
        printf("%I64d\n",answer);
    }
}
