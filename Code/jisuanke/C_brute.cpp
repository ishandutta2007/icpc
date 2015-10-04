#include <bits/stdc++.h>

int A[3],L[3],R[3],n;
int comb[500 + 1][500 + 1];

int work() {
    int ret = 0;
    for (int a = L[0]; a <= R[0]; ++ a) {
        if (a > n) break;
        for (int b = L[1]; b <= R[1]; ++ b) {
            if (a + b > n) break;
            for (int c = L[2]; c <= R[2]; ++ c) {
                if (a + b + c > n) break;
                ret += comb[A[0]][a] * comb[A[1]][b] % 47
                    * comb[A[2]][c] % 47;
                if (ret >= 47) {
                    ret -= 47;
                }
            }
        }
    }
    return ret;
}

int main() {
    for (int i = 0; i <= 500; ++ i) {
        comb[i][i] = comb[i][0] = 1;
        for (int j = 1; j < i; ++ j) {
            comb[i][j] = comb[i - 1][j] + comb[i - 1][j - 1];
            if (comb[i][j] >= 47) {
                comb[i][j] -= 47;
            }
        }
    }
    int cas;
    scanf("%d",&cas);
    while (cas--) {
        for (int i = 0; i < 3; ++ i) {
            scanf("%d%d%d",A + i,L + i,R + i);
        }
        scanf("%d",&n);
        printf("%d\n",work());
    }
}
