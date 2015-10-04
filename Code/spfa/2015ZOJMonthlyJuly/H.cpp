#include <bits/stdc++.h>

int n,m,nq;
const int N = 50000 + 5;
std::vector<int> back[N];
int answer[N];

int main() {
    while (scanf("%d%d%d",&n,&m,&nq) == 3) {
        for (int i = 1; i <= n; ++ i) {
            back[i].clear();
        }
        for (int i = 0; i < m; ++ i) {
            int a,b;
            scanf("%d%d",&a,&b);
            back[a].push_back(b);
        }
        int a = n,b = n;
        for (int i = n; i >= 1; -- i) {
            for (auto t : back[i]) {
                if (t < b) {
                    b = t;
                    if (a > b) {
                        std::swap(a,b);
                    }
                }
            }
            answer[i] = i - std::min(b,i);
        }
        while (nq--) {
            int t;
            scanf("%d",&t);
            printf("%d\n",answer[t]);
        }
    }
}
