#include <bits/stdc++.h>
typedef long long LL;

int dp[15][3][1 << 6][47 * 3 + 1];
std::vector<int> L[3],R[3],A[3],num;
int len;
int comb[47 + 1][47 + 1];

inline void add(int &a,int b) {
    a += b;
    if (a >= 47) a -= 47;
}

void show(const std::vector<int> &A) {
    for (int i = len - 1; i >= 0; -- i) {
        printf("%d ",A[i]);
    }
    puts("");
}

int work() { 
    memset(dp,0,sizeof(dp));
    for (int k = 0; k < 47; ++ k) {
        int mask = 0;
        if (L[0][0] > k) {
            mask ^= 1 << 0;
        }
        if (R[0][0] < k) {
            mask ^= 1 << 1;
        }
        dp[0][0][mask][k] = comb[A[0][0]][k];
    }

    for (int i = 0; i < len; ++ i) {
        for (int j = 0; j < 3; ++ j) {

            int ni = i,nj = j + 1;

            if (j == 2) {
                ni ++;
                nj = 0;
                if (ni == len) {
                    break;
                }
            }

            for (int mask = 0; mask < 1 << 6; ++ mask) {
                for (int s = 0; s <= 3 * 47; ++ s) {
                    if (dp[i][j][mask][s] == 0) continue;
                    for (int v = 0; v < 47; ++ v) {
                        int t = -1;
                        if (j == 2) {
                            t = (std::max(0,s - num[i]) + 46) / 47 + v;
                        } else {
                            t = s + v;
                        }
                        int nmask = mask;
                        if ((mask >> (nj << 1 | 1) & 1) && v < R[nj][ni]) {
                            nmask ^= 1 << (nj << 1 | 1);
                        }
                        if ((mask >> (nj << 1) & 1) && v > L[nj][ni]) {
                            nmask ^= 1 << (nj << 1);
                        }
                        if (v > R[nj][ni]) {
                            nmask |= 1 << (nj << 1 | 1);
                        }
                        if (v < L[nj][ni]) {
                            nmask |= 1 << (nj << 1);
                        }
                        add(dp[ni][nj][nmask][t],dp[i][j][mask][s] * comb[A[nj][ni]][v] % 47);
                    }
                }
            }
        }
    }
    return dp[len - 1][2][0][0];
}

void decompose(std::vector<int> &A,LL a) {
    A.clear();
    while (a) {
        A.push_back(a % 47);
        a /= 47;
    }
}

int main() {
    for (int i = 0; i <= 47; ++ i) {
        comb[i][i] = comb[i][0] = 1;
        for (int j = 1; j < i; ++ j) {
            comb[i][j] = comb[i - 1][j] + comb[i - 1][j - 1];
            if (comb[i][j] >= 47) comb[i][j] -= 47;
        }
    }
    int cas;
    scanf("%d",&cas);
    while (cas--) {
        for (int i = 0; i < 3; ++ i) {
            LL a,l,r;
            scanf("%lld%lld%lld",&a,&l,&r);
            decompose(A[i],a);
            decompose(L[i],l);
            decompose(R[i],r);
        }
        LL n;
        scanf("%lld",&n);
        decompose(num,n);
        len = num.size();
        for (int i = 0; i < 3; ++ i) {
            len = std::max(len,(int)A[i].size());
            len = std::max(len,(int)L[i].size());
            len = std::max(len,(int)R[i].size());
        }
        len ++;
        for (int i = 0; i < 3; ++ i) {
            A[i].resize(len);
            L[i].resize(len);
            R[i].resize(len);
        }
        num.resize(len);
        printf("%d\n",work());
    }
}
