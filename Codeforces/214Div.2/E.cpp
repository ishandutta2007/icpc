/* Created Time: Monday, November 25, 2013 AM09:14:22 CST */
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int N = 2222;
const int INF = 0x3f3f3f3f;
int n,m,k,s;
int mat[2][N][9],cp[9][9],ct[2][9];
void tomin(int &a,int b) { if (a>b) a=b; }
void tomax(int &a,int b) { if (a<b) a=b; }
void work() {
    memset(ct,0xf3,sizeof(ct));
    for (int i = m-1; i >= 0; i --) {
        for (int j = 0; j < k; j ++) {
            tomax(ct[0][j],i-mat[0][i][j]);
            tomax(ct[1][j],i+mat[1][i][j]);
        }
        for (int j = 0; j < k; j ++) {
            for (int r = 0; r < k; r ++) {
                tomax(cp[j][r],ct[0][r]-i+mat[1][i][j]);
                tomax(cp[j][r],ct[1][r]-i-mat[0][i][j]);
                tomax(cp[r][j],cp[j][r]);
            }
        }
    }
    int d,ans = 0;
    scanf("%d",&d);
    d --;
    for (int i = 1; i < s; i ++) {
        int x;
        scanf("%d",&x);
        x --;
        tomax(ans,cp[d][x]);
        d = x;
    }
    printf("%d\n",ans);
}
int main() {
    scanf("%d%d%d%d",&n,&m,&k,&s);
    memset(mat[0],INF,sizeof(mat[0]));
    memset(mat[1],-1,sizeof(mat[1]));
    for (int i = 0; i < n; i ++)
        for (int j = 0; j < m; j ++) {
            int d;
            scanf("%d",&d);
            d --;
            tomin(mat[0][j][d],i);
            tomax(mat[1][j][d],i);
        }
    work();
    return 0;
}
