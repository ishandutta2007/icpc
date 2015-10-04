#include <bits/stdc++.h>


const int N = 200000 + 5;

int dsu[2][N];

int n;
int nq;

int Find(int *dsu,int x) {
    int y = x;
    while (y != dsu[y]) y = dsu[y];
    while (x != y) {
        int z = dsu[x];
        dsu[x] = y;
        x = z;
    }
    return y;
}

int main() {
    scanf("%d%d",&n,&nq);
    for (int i = 1; i <= n + 1; ++ i) {
        dsu[0][i] = dsu[1][i] = i;
    }
    while (nq --) {
        int op,a,b;
        scanf("%d%d%d",&op,&a,&b);
        if (op == 1) {
            a = Find(dsu[0],a);
            b = Find(dsu[0],b);
            dsu[0][a] = b;
        } else if (op == 2) {
            for (int i = Find(dsu[1],a); i < b; ) {
                int j = Find(dsu[1],i + 1);
                int x = Find(dsu[0],i);
                int y = Find(dsu[0],j);
                dsu[0][x] = y;
                dsu[1][i] = j;
                i = j;
            }
        } else {
            puts(Find(dsu[0],a) == Find(dsu[0],b) ? 
                    "YES" : "NO");
        }
    }
}
