#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <functional>
#include <vector>
#include <map>
#include <set>

const int N = 1000 + 5;
int n,d,K,mat[N][N];

void solve(int n,int day,int base) {
    if (day==d) {
        return ;
    }
    if (n<=K) {
        for(int i = day; i < d; ++ i) {
            for (int j = 0; j < n; ++ j) {
                mat[i][base+j] = j;
            }
        }
        return ;
    }
    int block = n/K + (n%K!=0);
    for (int i = 0; i < n; ++ i) {
        mat[day][i+base] = i/block;
    }
    for (int i = 0; i < n; i += block) {
        solve(std::min(n-i,block),day+1,base+i);
    }
}

int main() {
    scanf("%d%d%d",&n,&K,&d);
    for (int x = 1,i = 1; i <= d; ++ i) {
        x *= K;
        if (x>=n) break;
        if (i==d) {
            puts("-1");
            return 0;
        }
    }
    if (K>=n) {
        for (int i = 1; i <= d; ++ i) {
            for (int j = 1; j <= n; ++ j) {
                printf("%d%c",j," \n"[j==n]);
            }
        }
        return 0;
    }
    solve(n,0,0);
    for (int i = 0; i < d; ++ i) {
        for (int j = 0; j < n; ++ j) {
            printf("%d%c",mat[i][j]+1," \n"[j==n-1]);
        }
    }
    return 0;
}

