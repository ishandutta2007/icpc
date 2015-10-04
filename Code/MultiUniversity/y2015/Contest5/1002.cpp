#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int a[500005];

int n, m, z, l;

void work() {
    scanf("%d%d%d%D", &n, &m, &z, &l);
    a[1] = 0;
    for (int i = 2; i <= n; i++) {
        a[i] = (a[i -1] * 1LL * m  + z) % l;
    }
    int ret = 0;
    for (int i = 1; i <= n; i++) ret ^= (a[i] + a[i]);
    printf("%d\n", ret);
}

int main() {
    int T;
    scanf("%d", &T);
    for (int cas = 1; cas <= T; cas++) {
        work();
    }
    return 0;
}
