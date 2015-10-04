#include <stdio.h>
#include <string.h>
#include <algorithm>
typedef long long LL;

const int N = 20000 + 5;
char str[N];
int A[N],n,m,K;
int tr[50 * N][2],cnt[50 * N],tot;

int get_node() {
    tr[tot][0] = tr[tot][1] = 0;
    cnt[tot] = 0;
    return tot ++;
}

LL B[N];
int btot;

void work() {
    int len = 1;
    for ( ; ; ++ len) {
        btot = 0;
        if (len <= n) {
            LL mask = 0;
            for (int i = 0; i < n; ++ i) {
                mask = mask << 1 | A[i];
                mask &= (1ll << len) - 1;
                if (i >= len - 1)
                    B[btot++] = mask;
            }
            std::sort(B,B + btot);
            btot = std::unique(B,B + btot) - B;
        }
        if ((1ll << len) - btot >= K) {
            break;
        } else {
            K -= (1ll << len) - btot;
        }
    }
    tot = 0;
    get_node();
    get_node();
    for (int I = 0; I < btot; ++ I) {
        LL mask = B[I];
        for (int u = 1,i = len - 1; i >= 0; -- i) {
            int c = mask >> i & 1;
            if (tr[u][c] == 0) {
                tr[u][c] = get_node();
            }
            u = tr[u][c];
            cnt[u] ++;
        }
    }
    for (int u = 1,i = len - 1; i >= 0; -- i) {
        if ((1 << i) - cnt[tr[u][0]] >= K) {
            putchar('A');
            u = tr[u][0];
        } else {
            putchar('B');
            K -= (1 << i) - cnt[tr[u][0]];
            u = tr[u][1];
        }
    }
    puts("");
}

int main() {
    int cas;
    scanf("%d",&cas);
    while (cas--) {
        scanf("%s",str);
        n = strlen(str);
        for (int i = 0; i < n; ++ i)
            A[i] = str[i] == 'B';
        scanf("%d",&m);
        for (int i = 0; i < m; ++ i) {
            scanf("%d",&K);
            work();
        }
    }
}
