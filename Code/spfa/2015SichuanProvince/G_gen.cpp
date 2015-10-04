#include <bits/stdc++.h>

const int N = 1000 + 5;
int n,m;

int main() {
    freopen("G.data","w",stdout);
    srand(time(NULL));
    //while (scanf("%d%d",&n,&m) == 2) {
    {
        n = 10,m = 10;
        std::vector<int> W(n),P(n);
        for (int i = 0; i < n; ++ i) {
            W[i] = rand() % 1000000 + 1;
            P[i] = rand() % 3 + 1;
        }
        std::vector<std::pair<int,int>> e;
        for (int i = 0; i < n; i += 2) {
            for (int j = i + 1; j < n; j += 2) {
                e.push_back(std::make_pair(i + 1,j + 1));
            }
        }
        std::random_shuffle(e.begin(),e.end());
        m = std::min(m,(int)e.size());
        printf("%d %d\n",n,m);
        for (int i = 0; i < n; ++ i) {
            if (i) putchar(' ');
            printf("%d",W[i]);
        }
        puts("");
        for (int i = 0; i < n; ++ i) {
            if (i) putchar(' ');
            printf("%d",P[i]);
        }
        puts("");
        for (int i = 0; i < m; ++ i) {
            printf("%d %d\n",e[i].first,e[i].second);
        }
    }
}
