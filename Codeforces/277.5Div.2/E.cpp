#include <bits/stdc++.h>

const int N = 1000 + 5;
const double eps = 1e-8;
const double Inf = 1e16;
int n,L,X[N],Y[N],pre[N];
double dp[N];

double solve(double slop) {
	for (int i = 1; i <= n; ++ i) {
		dp[i] = Inf;
		for (int j = 0; j < i; ++ j) {
			double cost = dp[j] + sqrt(std::abs(X[i]-X[j]-L))\
						  - slop * Y[i];
			if (cost < dp[i]) {
				dp[i] = cost;
				pre[i] = j;
			}
		}
	}
	return dp[n];
}

int main() {
	scanf("%d%d",&n,&L);
	for (int i = 1; i <= n; ++ i) {
		scanf("%d%d",X+i,Y+i);
	}
	double l = 0,r = 5000;
	int step = 100;
	while (step --) {
		double mid = (l+r)/2;
		if (solve(mid) + eps > 0)
			l = mid;
		else
			r = mid;
	}
	solve(r);
	std::vector<int> answer;
	for (int i = n; i > 0; i = pre[i])
		answer.push_back(i);
	std::reverse(answer.begin(),answer.end());
	for (int x : answer)
		printf("%d ",x);
	puts("");
	return 0;
}
