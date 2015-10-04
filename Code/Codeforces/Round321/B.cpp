#include <bits/stdc++.h>

std::pair<int,int> A[100000];
int n,d;

int main() {
    scanf("%d%d",&n,&d);
    for (int i = 0; i < n; ++ i) {
        scanf("%d%d",&A[i].first,&A[i].second);
    }
    std::sort(A,A + n);
    long long answer = 0;
    long long cur = 0;
    for (int i = 0,j = 0; i < n; ++ i) {
        while (j < n && A[j].first - A[i].first < d) {
            cur += A[j].second;
            ++ j;
        }
        if (answer < cur)
            answer = cur;
        cur -= A[i].second;
    }
    printf("%I64d\n",answer);
}
