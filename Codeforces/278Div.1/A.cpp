#include <bits/stdc++.h>

const int INF = 0x3f3f3f3f;
int H[2],A[2],D[2];
int h,a,d;

int check(int x,int y) {
	int dt = A[x]-D[y];
	if (dt <= 0) return INF;
	return (H[y]+dt-1)/dt;
}

int main() {
	for (int i = 0; i < 2; ++ i)
		scanf("%d%d%d",H+i,A+i,D+i);
	scanf("%d%d%d",&h,&a,&d);
	int answer = INF;
	for (int i = 0; i <= 200; ++ i) {
		int dt = A[0]+i-D[1];
		if (dt <= 0) continue;
		int t = (H[1]+dt-1)/dt;
		for (int j = 0; j <= 100; ++ j) {
			int dx = A[1]-j-D[0];
			int cost = i*a+j*d;
			if (dx <= 0) {
				answer = std::min(answer,cost);
				continue;
			}
			int tmp = t*dx+1-H[0];
			if (tmp > 0)
				cost += tmp*h;
			answer = std::min(answer,cost);
		}
	}
	printf("%d\n",answer);
	return 0;
}
