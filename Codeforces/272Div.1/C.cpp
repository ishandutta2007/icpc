#include <bits/stdc++.h>
using LL = long long;

const int N = 2000 + 5;
const int INF = 0x3f3f3f3f;

char sa[N];
char sb[N];
int la,lb;
int dp[N][N];
int cost[N],right[N];
int answer[N];

inline void toMax(int &a,int b) {
	if (a < b) a = b;
}

inline void toMin(int &a,int b) {
	if (a > b) a = b;
}

int main() {
	scanf("%s%s",sa,sb);
	la = strlen(sa);
	lb = strlen(sb);
	memset(cost,INF,sizeof(cost));
	for (int i = 0; i+lb-1 < la; ++ i) {
		int t = 0,cur = 0;
		for (int j = i; j < la; ++ j) {
			if (sa[j] != sb[cur]) {
				t ++;
			} else {
				if (++cur == lb) {
					cost[i] = t;
					right[i] = j;
					break;
				}
			}
		}
	}
	memset(dp,INF,sizeof(dp));
	for (int i = 0; i < la; ++ i) {
		if (cost[i] != INF) {
			toMin(dp[right[i]][1],cost[i]);
		}
	}
	for (int i = 0; i < la; ++ i) {
		for (int j = 1; j <= i+1; ++ j) {
			if (dp[i][j] == INF) continue;
			toMin(dp[i+1][j],dp[i][j]);
			if (cost[i+1] != INF) {
				toMin(dp[right[i+1]][j+1],dp[i][j]+cost[i+1]);
			}
		}
	}
	for (int i = 0; i <= la; ++ i) {
		if (dp[la][i] != INF) {
			toMax(answer[dp[la][i]],i);
		}
	}
	for (int i = 0; i < la; ++ i) {
		toMax(answer[i+1],std::min((la-i-1)/lb,answer[i]));
	}
	for (int i = 0; i <= la; ++ i) {
		printf("%d ",answer[i]);
	}
	puts("");
	return 0;
}
