#include <bits/stdc++.h>

const int N = 100000 + 5;
int n,A[N];

int main() {
    scanf("%d",&n);
    for (int i = 1; i <= n; ++ i) {
        scanf("%d",A + i);
    }
    for (int i = n; i >= 1; -- i) {
        A[i] = std::min(A[i],A[i + 1] + 1);
    }
    for (int i = 1; i <= n; ++ i) {
        A[i] = std::min(A[i],A[i - 1] + 1);
    }
    printf("%d\n",*std::max_element(A + 1,A + n + 1));
}
