#include <bits/stdc++.h>


const int N = 1000000 + 5;
int n,A[N];
int cnt[N];

int work() {
    std::sort(A,A + n);
    for (int i = 0; i < n; ++ i) {
        int a = A[i];
        int t = cnt[a] + 1;
        for (int j = a; j < N; j += a) {
            cnt[j] = std::max(cnt[j],t);
        }
    }
    return *std::max_element(cnt,cnt + N);
}

int main() {
    scanf("%d",&n);
    for (int i = 0; i < n; ++ i) {
        scanf("%d",A + i);
    }
    printf("%d\n",work());
}
