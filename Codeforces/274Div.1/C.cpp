#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <vector>
#include <set>

const int N = 5000 + 5;
const int MOD = (int)1e9+7;
int n,A,B,K;
int dp[N][N];

void add(int &a,int b) {
	a += b; if (a >= MOD) a -= MOD;
	if (a < 0) a += MOD;
}

int main() {
	scanf("%d%d%d%d",&n,&A,&B,&K);
	dp[0][A] = 1;
	dp[0][A+1] = MOD-1;
	for (int i = 0; i <= K; ++ i) {
		for (int j = 1; j <= n; ++ j) {
			add(dp[i][j],dp[i][j-1]);
			int D = std::abs(B-j);
			int low = std::max(1,j-D+1);
			int high = std::min(j+D-1,n);
			if (low < j) {
				add(dp[i+1][low],dp[i][j]);
				add(dp[i+1][j],MOD-dp[i][j]);
			}
			if (high > j) {
				add(dp[i+1][j+1],dp[i][j]);
				add(dp[i+1][high+1],MOD-dp[i][j]);
			}
		}
	}
	int answer = 0;
	for (int i = 1; i <= n; ++ i) {
		add(answer,dp[K][i]);
	}
	printf("%d\n",answer);
	return 0;
}
