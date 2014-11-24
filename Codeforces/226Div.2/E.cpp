#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <vector>
using namespace std;
typedef long long lld;
typedef vector<lld> vec;
typedef vector<vec> mat;
lld n,sx,sy,dx,dy,t;

mat mul(mat A,mat B) {
        mat ret(A.size(),vec(B[0].size()));
        for (int i = 0; i < (int)A.size(); i ++)
                for (int j = 0; j < (int)B[0].size(); j ++)
                        for (int k = 0; k < (int)A[0].size(); k ++)
                                (ret[i][j] += (A[i][k]*B[k][j])%n) %= n;
        return ret;
}
int main() {
        scanf("%lld%lld%lld%lld%lld%lld",&n,&sx,&sy,&dx,&dy,&t);
        sx --; sy --; dx = (n+dx)%n; dy = (n+dy)%n;
        mat A(1,vec(6));
        A[0][0] = sx; A[0][1] = sy; A[0][2] = dx; A[0][3] = dy; A[0][4] = 0; A[0][5] = 1;
        mat C(6,vec(6));
        C[0][0] = 2; C[0][1] = 1; C[0][2] = 1; C[0][3] = 1; C[0][4] = 0; C[0][5] = 0;
        C[1][0] = 1; C[1][1] = 2; C[1][2] = 1; C[1][3] = 1; C[1][4] = 0; C[1][5] = 0;
        C[2][0] = 1; C[2][1] = 0; C[2][2] = 1; C[2][3] = 0; C[2][4] = 0; C[2][5] = 0;
        C[3][0] = 0; C[3][1] = 1; C[3][2] = 0; C[3][3] = 1; C[3][4] = 0; C[3][5] = 0;
        C[4][0] = 1; C[4][1] = 1; C[4][2] = 1; C[4][3] = 1; C[4][4] = 1; C[4][5] = 0;
        C[5][0] = 2; C[5][1] = 2; C[5][2] = 2; C[5][3] = 2; C[5][4] = 1; C[5][5] = 1;

        while (t) {
                if (t&1) A = mul(A,C);
                C = mul(C,C);
                t >>= 1;
        }
        A[0][0] ++; A[0][1] ++;
        printf("%lld %lld\n",A[0][0],A[0][1]);
        return 0;
}
