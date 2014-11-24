#include <bits/stdc++.h>
using LL = long long;

const int N = 100000 + 5;
const int MOD = (int)1e9+7;
int n,dp[N][2];
std::vector<int> edges[N];

inline void add(int &a,int b) {
	a += b; if (a >= MOD) a -= MOD;
}

void dfs(int u) {
	for (int v : edges[u]) 
		dfs(v);
	int left[2] = {0,0};
	int right[2] = {0,0};
	int sym[2] = {0,0};
	int mex = 0;
	for (int v : edges[u]) {
		int tmp[2] = {left[0],left[1]};
		for (int i = 0; i < 2; ++ i)
			for (int j = 0; j < 2; ++ j)
				add(tmp[i^j^1],(LL)left[i]*dp[v][j]%MOD);
		add(tmp[0],dp[v][0]);
		add(tmp[1],dp[v][1]);
		left[0] = tmp[0];
		left[1] = tmp[1];
	}
	std::reverse(edges[u].begin(),edges[u].end());
	for (int v : edges[u]) {
		int tmp[2] = {right[0],right[1]};
		for (int i = 0; i < 2; ++ i)
			for (int j = 0; j < 2; ++ j)
				add(tmp[i^j^1],(LL)right[i]*dp[v][j]%MOD);
		add(tmp[0],dp[v][0]);
		add(tmp[1],dp[v][1]);
		right[0] = tmp[0];
		right[1] = tmp[1];
	}
	for (int v : edges[u]) {
		int tmp[2] = {sym[0],sym[1]};
		for (int i = 0; i < 2; ++ i)
			add(tmp[i^1],(LL)sym[i]*dp[v][0]%MOD);
		add(tmp[0],dp[v][0]);
		sym[0] = tmp[0];
		sym[1] = tmp[1];
	}
	for (int v : edges[u]) {
		add(mex,(LL)mex*dp[v][1]%MOD);
		add(mex,dp[v][1]);
	}

	dp[u][0] = (left[0] + right[0]) % MOD;
	dp[u][1] = (left[1] + right[1]) % MOD;
	add(dp[u][0],MOD-sym[0]);
	add(dp[u][1],MOD-mex);
	std::swap(dp[u][0],dp[u][1]);
	add(dp[u][0],1);
}

int main() {
	scanf("%d",&n);
	for (int i = 1; i < n; ++ i) {
		int x;
		scanf("%d",&x); x --;
		edges[x].push_back(i);
	}
	dfs(0);
	int answer = 0;
	add(answer,dp[0][0]);
	add(answer,dp[0][1]);
	printf("%d\n",answer);
	return 0;
}
