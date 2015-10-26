#include <bits/stdc++.h>

const int N = 500000 + 5;
int A[N],n;

void work() {
    int ret = 0;
    for (int i = 0; i < n; ) {
        while (i + 1 < n && A[i] == A[i + 1]) ++ i;
        if (i + 1 == n)
            break;
        int j = i + 1;
        while (j + 1 < n && A[j] != A[j + 1]) ++ j;
        ret = std::max(ret,j - i >> 1);
        for (int l = i + 1,r = j - 1; l <= r; ++ l,-- r) {
            A[l] = A[l - 1];
            A[r] = A[r + 1];
        }
        i = j + 1;
    }
    printf("%d\n",ret);
    for (int i = 0; i < n; ++ i) {
        if (i) putchar(' ');
        printf("%d",A[i]);
    }
    puts("");
}

int main() {
    scanf("%d",&n);
    for (int i = 0; i < n; ++ i) {
        scanf("%d",A + i);
    }
    work();
}
