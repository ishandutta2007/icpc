#include <stdio.h>
#include <string.h>
#include <algorithm>

const int N = 100000 + 5;
int n;
int A[N];

int main() {
    while (scanf("%d",&n) == 1) {
        A[0] = 1;
        for (int i = 1; i < n; ++ i) {
            int x;
            scanf("%d",&x); x --;
            A[i] = A[x] + 1;
        }
        std::sort(A,A + n);
        double answer = 0.;
        double a = 1,b = 1;
        for (int i = 0; i < n; ++ i)
            b = b * 2;
        for (int i = n - 1; i >= 0 && n - i <= 150; -- i) {
            a = a * 2;
            b = b / 2;
            double x = 0;
            for (int j = i + 1; j < n; ++ j) {
                x += (double)A[j] / (A[j] + A[i]);
            }
            answer += x * A[i] / (a - (n + 1) / b);
        }
        printf("%.6f\n",answer);
    }
}
