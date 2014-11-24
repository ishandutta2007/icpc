#include <bits/stdc++.h>

const int N = 100000 + 5;
const int INF = 0x3f3f3f3f;
int n,S,L,A[N],dp[N],left[N];
int high[N],low[N],dsu[N];

int Find(int x) {
	if (x == dsu[x]) return x;
	int y = dsu[x];
	int z = Find(y);
	high[x] = std::max(high[x],high[y]);
	low[x] = std::min(low[x],low[y]);
	return dsu[x] = z;
}

int main() {
	scanf("%d%d%d",&n,&S,&L);
	std::deque<int> que;
	for (int i = 1; i <= n; ++ i) {
		scanf("%d",A+i);
		dsu[i-1] = dsu[i] = i;
		high[i] = low[i] = A[i];
		if (L<=i && dp[i-L]!=INF) {
			while (!que.empty() && dp[que.back()]>=dp[i-L])
				que.pop_back();
			que.push_back(i-L);
		}
		int l = 1,r = i;
		while (l <= r) {
			int mid = l+r>>1;
			Find(i-mid+1);
			if (high[i-mid+1]-low[i-mid+1] <= S)
				l = mid+1;
			else
				r = mid-1;
		}
		l --;
		while (!que.empty() && que.front()<i-l) que.pop_front();
		if (!que.empty()) {
			dp[i] = dp[que.front()]+1;
		} else {
			dp[i] = INF;
		}
	}
	printf("%d\n",dp[n]==INF ? -1 : dp[n]);
	return 0;
}
