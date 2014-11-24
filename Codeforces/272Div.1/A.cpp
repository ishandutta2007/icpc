#include <bits/stdc++.h>
using LL = long long;

const int MOD = (int)1e9+7;
const int inv2 = MOD+1>>1;

inline void add(int &a,int b) {
	a += b; if (a >= MOD) a -= MOD;
	if (a < 0) a += MOD;
}

int calc(int a,int b) {
	int ret = 0;
	for (int i = 1; i < b; ++ i) {
		LL slop = (LL)b*i%MOD;
		LL R = a;
		LL delta = R*i%MOD;
		delta += (slop + R*slop) % MOD * R % MOD * inv2 % MOD;
		add(ret,delta%MOD);
	}
	return ret;
}

int main() {
	int a,b;
	scanf("%d%d",&a,&b);
	printf("%d\n",calc(a,b));
	return 0;
}
