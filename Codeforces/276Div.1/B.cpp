#include <stdio.h>
#include <string.h>
#include <algorithm>
typedef long long LL;

const int N = 2000000 + 5;
int A[N],left[N];

int main() {
	int n;
	scanf("%d",&n);
	for (int i = 0; i < n; ++ i) {
		int x;
		scanf("%d",&x);
		A[x] ++;
	}
	for (int i = 1; i < N; ++ i) {
		left[i] = left[i-1];
		if (A[i]) left[i] = i;
	}
	int answer = 0;
	for (int i = 1; i <= 1000000; ++ i) {
		if (!A[i]) continue;
		for (int j = i+i; j < N; j += i) {
			if (left[j-1]==0) continue;
			int v = left[j-1];
			if (j-v >= i) continue;
			answer = std::max(answer,i-(j-v));
		}
	}
	printf("%d\n",answer);
	return 0;
}
