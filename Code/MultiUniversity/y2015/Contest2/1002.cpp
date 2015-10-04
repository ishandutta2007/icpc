#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int INF = 0x3f3f3f3f;

const int dir[8][2] = {
    1, 0, 1, 1, 0, 1, -1, 1, -1, 0, -1, -1, 0, -1, 1, -1
};

int n, m, x, y;

int isok(int X, int Y, int L) {
    if (X == x && Y == y) return true;
    if (X <= 0 || X > n || Y <= 0 || Y > m) return true;
    int g1, g2, g3, g4;
    if (X-1 == x && Y == y) {
        g1 = INF;
    }else {
        g1 = X;
    }
    if (X+1 == x && Y == y) {
        g2 = INF;
    }else {
        g2 = n - X + 1;
    }
    if (Y-1 == y && X == x) {
        g3 = INF;
    }else {
        g3 = Y;
    }
    if (Y+1 == y && X == x) {
        g4 = INF;
    }else {
        g4 = m - Y + 1;
    }
    return min(min(g1, g2), min(g3, g4)) <= L;
}

int check(int L) {
    for (int i = 0; i < 8; i++) {
        int X = x + dir[i][0];
        int Y = y + dir[i][1];
        if (!isok(X, Y, L)) {
            return false;
        }
    }
    return isok(n/2, m/2, L) && isok(n-n/2, m/2, L) &&
        isok(n/2, m-m/2, L) && isok(n-n/2, m-m/2, L);
}

void work() {
    int l = 1, r = max(n, m);
    while (r >= l) {
        int mid = (r + l) >> 1;
        if (check(mid)) {
            r = mid - 1;
        }else {
            l = mid + 1;
        }
    }
    printf("%d\n", r + 1);
}

int main() {
    while (scanf("%d%d%d%d", &n, &m, &x, &y) == 4) {
        work();
    }
    return 0;
}
