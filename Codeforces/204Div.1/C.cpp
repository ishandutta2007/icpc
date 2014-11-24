/* Created Time: Friday, November 15, 2013 PM06:23:23 CST */
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <vector>
using namespace std;
int n,m,f[21][21],a[21],b[21];
unsigned INF = 2e9+7;
unsigned mat[30][21][21];
int work() {
    vector <unsigned> ret(21,INF);
    ret[0] = 0;
    for (int c = 0; m>>c; c ++) {
        if (m&1<<c) {
            vector <unsigned> tmp(21,INF);
            for (int i = 0; i <= 20; i ++) 
                for (int j = 0; j <= 20; j ++)
                    tmp[j] = min(tmp[j],ret[i]+mat[c][i][j]);
            ret.swap(tmp);
        }
        for (int k = 0; k <= 20; k ++)
            for (int i = 0; i <= 20; i ++)
                for (int j = 0; j <= 20; j ++)
                    mat[c+1][i][j] = min(mat[c+1][i][j],mat[c][i][k]+mat[c][k][j]);
    }
    return ret[0];
}
int main() {
    scanf("%d%d",&n,&m);
    for (int i = 0; i < n; i ++) scanf("%d",&a[i]);
    for (int i = 0; i < n; i ++) scanf("%d",&b[i]);
    memset(mat,0x7f,sizeof(mat));
    for (int s = 0; s <= 20; s ++) {
        memset(f,0x3f,sizeof(f));
        f[0][s] = 0;
        for (int i = 0; i < n; i ++) {
            for (int j = 0; j <= 19; j ++) f[i+1][j+1] = min(f[i+1][j+1],f[i][j]+a[i]);
            for (int j = 1; j <= 20; j ++) f[i+1][j-1] = min(f[i+1][j-1],f[i][j]+b[i]);
        }
        for (int t = 0; t <= 20; t ++) mat[0][s][t] = f[n][t];
    }
    printf("%d\n",work());
    return 0;
}
