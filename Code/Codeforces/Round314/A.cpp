#include <bits/stdc++.h>

const int N = 100000 + 5;
int n,A[N];

void work() {
    printf("%d %d\n",A[1] - A[0],A[n - 1] - A[0]);
    for (int i = 1; i + 1 < n; ++ i) {
        printf("%d %d\n",
                std::min(A[i] - A[i - 1],A[i + 1] - A[i]),
                std::max(A[i] - A[0],A[n - 1] - A[i]));
    }
    printf("%d %d\n",A[n - 1] - A[n - 2],A[n - 1] - A[0]);
}


int main() {
    scanf("%d",&n);
    for (int i = 0; i < n; ++ i) {
        scanf("%d",A + i);
    }
    work();
}
