#include <bits/stdc++.h>

int A[6];

int work() {
    int ret = 0;
    while (A[1] > 0) {
        ret -= A[1] + A[1] - 1;
        A[1] --;
    }
    while (A[3] > 0) {
        ret -= A[3] + A[3] - 1;
        A[4] ++;
        A[3] --;
    }
    while (A[5] > 0) {
        ret -= A[5] + A[5] - 1;
        A[4] ++;
        A[5] --;
    }
    while (A[4] > 0) {
        ret += A[4] + A[4] - 1;
        A[4] --;
    }
    return ret;
}

int main() {
    for (int i = 0; i < 6; ++ i) {
        scanf("%d",A + i);
    }
    printf("%d\n",work());
}

