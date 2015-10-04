#include <stdio.h>
#include <string.h>
#include <algorithm>

const int N = 500 + 5;
int C[N][N];
int n,m,nq;
int A[N][N];

void modify(int *C,int y,int v) {
    for (int i = y; i < N; i += i & -i)
        C[i] ^= v;
}

void modify2(int x,int y,int v) {
    for (int i = x; i < N; i += i & -i) 
        modify(C[i],y,v);
}

int query(int *C,int y) {
    int ret = 0;
    for (int i = y; i > 0; i -= i & -i)
        ret ^= C[i];
    return ret;
}

int query2(int x,int y) {
    int ret = 0;
    for (int i = x; i > 0; i -= i & -i)
        ret ^= query(C[i],y);
    return ret;
}

int main() {
    int cas;
    scanf("%d",&cas);
    while (cas--) {
        scanf("%d%d%d",&n,&m,&nq);
        memset(C,0,sizeof(C));
        for (int i = 1; i <= n; ++ i) {
            for (int j = 1; j <= m; ++ j) {
                scanf("%d",&A[i][j]);
                modify2(i,j,A[i][j]);
            }
        }
        while (nq--) {
            int op;
            scanf("%d",&op);
            if (op == 1) {
                int a,b,c,d;
                scanf("%d%d%d%d",&a,&b,&c,&d);
                int answer = query2(c,d) ^ query2(a - 1,d)
                    ^ query2(c,b - 1) ^ query2(a - 1,b - 1);
                puts(answer ? "Yes" : "No");
            } else {
                int x,y,z;
                scanf("%d%d%d",&x,&y,&z);
                modify2(x,y,z ^ A[x][y]);
                A[x][y] = z;
            }
        }
    }
}

