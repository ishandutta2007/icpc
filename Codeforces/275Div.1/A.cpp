#include <bits/stdc++.h>
using LL = long long;

int n,K;

int main() {
	scanf("%d%d",&n,&K);
	for (int i = 0; i <= K>>1; ++ i) {
		printf("%d ",i+1);
		if ((K&1)==1 || i!=(K>>1))
			printf("%d ",K+1-i);
	}
	for (int i = K+2; i <= n; ++ i) {
		printf("%d ",i);
	} 
	puts("");
	return 0;
}
