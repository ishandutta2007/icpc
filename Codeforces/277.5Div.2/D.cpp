#include <bits/stdc++.h>
typedef long long LL;

const int N = 3000 + 5;
std::vector<int> edges[N];
int n,m,count[N];

int main() {
	scanf("%d%d",&n,&m);
	for (int i = 0; i < m; ++ i) {
		int a,b;
		scanf("%d%d",&a,&b); a --; b --;
		edges[a].push_back(b);
	}
	LL answer = 0;
	for (int i = 0; i < n; ++ i) {
		for (int j = 0; j < n; ++ j) {
			count[j] = 0;
		}
		for (int v : edges[i]) {
			for (int vv : edges[v]) {
				count[vv] ++;
			}
		}
		for (int j = 0; j < n; ++ j) {
			if (i != j)
				answer += (count[j]-1)*count[j]/2;
		}
	}
	printf("%I64d\n",answer);
	return 0;
}
