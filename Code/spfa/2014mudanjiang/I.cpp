#include <bits/stdc++.h>

int main() {
    int cas;
    scanf("%d",&cas);
    while (cas--) {
        int n;
        char str[4];
        scanf("%d%s",&n,str);
        int P[100];
        for (int i = 0; i < n; ++ i) {
            scanf("%d",P + i);
        }
        double answer = 0.;
        for (int i = 0; i < n; ++ i) {
            if (P[i] == 0) continue;
            if (str[0] == 'b') {
                answer -= P[i] * log(P[i] / 100.) / log(2);
            } else if (str[0] == 'n') {
                answer -= P[i] * log(P[i] / 100.);
            } else {
                answer -= P[i] * log(P[i] / 100.) / log(10);
            }
        }
        printf("%.10f\n",answer / 100.);
    }
}
