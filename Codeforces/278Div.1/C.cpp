#include <bits/stdc++.h>

const int N = 100000 + 5;
int inv[N],n;

int main() {
	scanf("%d",&n);
	if (n == 1) {
		printf("YES\n1\n");
		return 0;
	} else if (n == 4) {
		printf("YES\n1 3 2 4\n");
		return 0;
	}
	for (int i = 2; i < n; ++ i)
		if (n%i == 0) {
			puts("NO");
			return 0;
		}
	puts("YES");
	printf("%d\n",1);
	inv[1] = 1;
	for (int i = 2; i < n; ++ i) {
		inv[i] = (long long)(n-n/i)*inv[n%i]%n;
		printf("%d\n",(int)((long long)i*inv[i-1]%n));
	}
	printf("%d\n",n);
	return 0;
}
