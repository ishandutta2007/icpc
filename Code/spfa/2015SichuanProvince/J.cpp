#include <stdio.h>
#include <string.h>
#include <algorithm>

const int INF = 0x3f3f3f3f;
const int N = 1000 + 5;
int dir[4][2] = {1,0,0,-1,-1,0,0,1};
int n;
int X[N],Y[N];
bool A[4][N];

int work() {
    memset(A,0,sizeof(A));
    int x = 0,y = 0,d = 0;
    for (int step = 0; ; ++ step) {
        int mx = INF;
        int p = -1;
        for (int i = 0; i < n; ++ i) {
            if (d == 0 || d == 2) {
                if (y != Y[i]) continue;
                if ((X[i] - x) * dir[d][0] < 0) continue;
            } else {
                if (x != X[i]) continue;
                if ((Y[i] - y) * dir[d][1] < 0) continue;
            }
            int dt = std::abs(x - X[i]) + std::abs(y - Y[i]);
            if (dt < mx) {
                mx = dt;
                p = i;
            }
        }
        if (p == -1) {
            return step;
        } else if (A[d][p]) {
            return -1;
        }
        A[d][p] = true;
        x = X[p] - dir[d][0];
        y = Y[p] - dir[d][1];
        d = (d + 1) % 4;
    }
}


int main() {
    while (scanf("%d",&n) == 1) {
        for (int i = 0; i < n; ++ i) {
            scanf("%d%d",X + i,Y + i);
        }
        printf("%d\n",work());
    }
}
