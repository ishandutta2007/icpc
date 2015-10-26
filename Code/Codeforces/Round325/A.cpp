#include <bits/stdc++.h>
typedef long long LL;


const int N = 4000 + 5;

LL V[N],D[N],P[N];

int n;

void boom(int u) {
    for (int i = u + 1; i < n; ++ i) {
        if (P[i] < 0) continue;
        P[i] -= D[u];
        if (P[i] < 0) {
            boom(i);
        }
    }
}

void work() {
    std::vector<int> answer;
    for (int i = 0; i < n; ++ i) {
        if (P[i] < 0) continue;
        answer.push_back(i);
        std::vector<int> duang;
        for (int j = i + 1,v = V[i]; j < n && v; ++ j) {
            if (P[j] < 0) continue;
            P[j] -= v --;
            if (P[j] < 0) {
                duang.push_back(j);
            }
        }
        for (auto t : duang) {
            boom(t);
        }
    }
    printf("%d\n",answer.size());
    for (int i = 0; i < answer.size(); ++ i) {
        if (i) putchar(' ');
        printf("%d",answer[i] + 1);
    }
    puts("");
}

int main() {
    scanf("%d",&n);
    for (int i = 0; i < n; ++ i) {
        scanf("%I64d%I64d%I64d",V + i,D + i,P + i);
    }
    work();
}
