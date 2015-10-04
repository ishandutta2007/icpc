#include <bits/stdc++.h>
typedef std::vector<int> vec;
typedef std::vector<vec> mat;

inline void update(int &a,int b) {
    if (a < b) a = b;
}

const int N = 100 + 1;
int dp[N][N],n,T,A[N];

mat mul(const mat &A,const mat &B) {
    mat ret(A.size(),vec(B[0].size(),-1));
    for (int k = 0; k < A[0].size(); ++ k)
        for (int i = 0; i < A.size(); ++ i)
            for (int j = 0; j < B[0].size(); ++ j)
                if (A[i][k] != -1 && B[k][j] != -1)
                    update(ret[i][j],A[i][k] + B[k][j]);
    return ret;
}

int work() {
    mat R(300,vec(300,-1));
    memset(dp,-1,sizeof(dp));
    for (int i = 0; i < n; ++ i) {
        dp[i][i] = 1;
        for (int j = i; j < n; ++ j) {
            if (dp[i][j] == -1) continue;
            for (int k = j + 1; k < n; ++ k) {
                if (A[j] <= A[k])
                    update(dp[i][k],dp[i][j] + 1);
            }
            update(R[A[i]][A[j]],dp[i][j]);
        }
    }
    for (int i = 300 - 1; i > 0; -- i) {
        for (int j = i; j < 300; ++ j) {
            update(R[i - 1][j],R[i][j]);
        }
    }
    mat L(1,vec(300,-1));
    L[0][0] = 0;
    for ( ; T; T >>= 1) {
        if (T & 1) L = mul(L,R);
        R = mul(R,R);
    }
    int ret = 0;
    for (int i = 0; i < 300; ++ i) {
        update(ret,L[0][i]);
    }
    return ret;
}

int main() {
    scanf("%d%d",&n,&T);
    for (int i = 0; i < n; ++ i) {
        scanf("%d",A + i); A[i] -- ;
    }
    printf("%d\n",work());
}
