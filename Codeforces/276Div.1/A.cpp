#include <stdio.h>
#include <string.h>
#include <algorithm>
typedef long long LL;

const int N = 100000 + 5;
int n;

int count(LL x) {
	int ret = 0;
	for (int i = 0; i < 62; ++ i) {
		ret += x>>i&1;
	}
	return ret;
}

LL work(LL l,LL r) {
	LL ret = 0;
	for (int i = 62; i >= 0; -- i) {
		int a = l>>i&1;
		int b = r>>i&1;
		if (!a && b) {
			ret |= (1ll<<i)-1;
			break;
		} else if (a && b) {
			ret |= (1ll<<i);
		}
	}
	if (count(r) > count(ret)) {
		ret = r;
	}
	return ret;
}

int main() {
	scanf("%d",&n);
	for (int i = 0; i < n; ++ i) {
		LL l,r;
		scanf("%I64d%I64d",&l,&r);
		printf("%I64d\n",work(l,r));
	}
	return 0;
}
