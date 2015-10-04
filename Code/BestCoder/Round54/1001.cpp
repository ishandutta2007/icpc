#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <vector>

const int INF = ~0u >> 1;
int n,A[100];

int work() {
    int B[3] = {INF,INF,INF};
    for (int i = 0; i < n; ++ i) {
        int t = A[i];
        for (int j = 2; j * j <= t; ++ j) {
            while (t % j == 0) {
                B[2] = j;
                t /= j;
                std::sort(B,B + 3);
            }
        }
        if (t != 1) {
            B[2] = t;
            std::sort(B,B + 3);
        }
    }
    if (B[1] == INF) return -1;
    return B[0] * B[1];
}

int main() {
    int cas;
    scanf("%d",&cas);
    while (cas--) {
        scanf("%d",&n);
        for (int i = 0; i < n; ++ i) {
            scanf("%d",A + i);
        }
        printf("%d\n",work());
    }
}

