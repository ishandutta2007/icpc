#include <bits/stdc++.h>

const int N = 1000000 + 5;
std::vector<int> A[N];
int n;

void work() {
    int l = -1,r = -1;
    int len = n + 10;
    int number = 0;
    for (int i = 1; i <= 1000000; ++ i) {
        if (A[i].empty()) continue;
        if ((int)A[i].size() < number) continue;
        int ll = A[i][0];
        int rr = A[i].back();
        if (A[i].size() == number && rr - ll + 1 < len || A[i].size() > number) {
            len = rr - ll + 1;
            l = ll;
            r = rr;
            number = A[i].size();
        }
    }
    printf("%d %d\n",l,r);
}

int main() {
    scanf("%d",&n);
    for (int i = 1; i <= n; ++ i) {
        int x;
        scanf("%d",&x);
        A[x].push_back(i);
    }
    work();
}
