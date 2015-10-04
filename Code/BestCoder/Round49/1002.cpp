#include <bits/stdc++.h>

const int N = 40000 + 5;
char str[20000 + 5];
char A[40000 + 5];
int R[N];
bool Q[N],W[N];

bool work() {
    int tot = 0;
    A[tot++] = '#';
    for (int i = 0; str[i]; ++ i) {
        A[tot++] = str[i];
        A[tot++] = '#';
    }
    for (int i = 0; i < tot; ++ i) {
        Q[i] = W[i] = false;
    }
    R[0] = 1;
    int p = 0;
    for (int i = 1; i < tot; ++ i) {
        int t = 1;
        if (p + R[p] - 1 >= i) {
            t = std::max(t,std::min(R[2 * p - i],p + R[p] - i));
        }
        while (i - t >= 0 && i + t < tot && A[i - t] == A[i + t]) ++ t;
        R[i] = t;
        if (i + t > p + R[p]) {
            p = i;
        }
        if (i - t + 1 == 0) {
            Q[i + t - 1] = true;
        }
        if (i + t - 1 == tot - 1) {
            W[i - t + 1] = true;
        }
    }
    for (int i = 1; i < tot; ++ i) {
        if (Q[i] == true) {
            for (int j = i + 2; j + 1 < tot; j += 2) {
                if (W[j] == true) {
                    int p = i + j >> 1;
                    if (p + R[p] - 1 >= j - 1) {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

int main() {
    int cas;
    scanf("%d",&cas);
    while (cas--) {
        scanf("%s",str);
        puts(work() ? "Yes" : "No");
    }
}
