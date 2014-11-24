#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
#include <queue>
using namespace std;

#define mp make_pair
#define pb push_back
#define snuke(it,x) for (__typeof((x).begin()) it = (x).begin(); it != (x).end(); ++ it)

typedef long long lld;
const int N = 101000;
lld dp[N][2];
int a[N];

int main() {
	int n;
	scanf("%d",&n);
	for (int i = 1; i <= n; ++ i) {
		int x;
		scanf("%d",&x);
		a[x] ++;
	}
	for (int i = 1; i <= 100000; ++ i) {
		dp[i][0] = max(dp[i-1][0],dp[i-1][1]);
		dp[i][1] = dp[i-1][0] + (lld)i * a[i];
	}
	printf("%I64d\n",max(dp[100000][1],dp[100000][0]));
	return 0;
}

