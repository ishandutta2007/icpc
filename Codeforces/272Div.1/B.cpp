#include <bits/stdc++.h>

int n,K;

int main() {
	scanf("%d%d",&n,&K);
	printf("%d\n",(n*3-1<<1|1)*K);
	for (int i = 0; i < n; ++ i) {
		int base = i*3<<1;
		printf("%d %d %d %d\n",(base+1)*K,(base+2)*K
				,(base+3)*K,(base+5)*K);
	}
	return 0;
}
