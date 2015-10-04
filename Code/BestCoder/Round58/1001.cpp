#include <stdio.h>


const int N = 100000 + 5;
int A[N],n;
int B[N],C[N];
int vis[N],tim;

int main() {
    int cas;
    scanf("%d",&cas);
    while (cas--) {
        scanf("%d",&n);
        for (int i = 1; i <= n; ++ i) {
            scanf("%d",A + i);
        }
        for (int i = 1; i <= n; ++ i) {
            scanf("%d",B + i);
            C[A[i]] = B[i];
        }
        tim ++;
        int answer = 0;
        for (int i = 1; i <= n; ++ i) {
            if (vis[i] == tim) continue;
            if (i == C[i]) {
                answer ++;
                continue;
            }
            int cnt = 0;
            for (int p = i; vis[p] != tim; p = C[p]) {
                vis[p] = tim;
                cnt ++;
            }
            answer += cnt - 1;
        }
        printf("%d\n",answer);
    }
}
