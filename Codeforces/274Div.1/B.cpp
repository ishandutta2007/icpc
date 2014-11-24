#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <vector>
#include <set>

const int N = 100000 + 5;
int n,L,X,Y,A[N];
std::set<int> set;

int main() {
	scanf("%d%d%d%d",&n,&L,&X,&Y);
	for (int i = 0; i < n; ++ i) {
		scanf("%d",A+i);
		set.insert(A[i]);
	}
	bool fx = false,fy = false;
	for (int i = 0; i < n; ++ i) {
		if (set.find(A[i]+X) != set.end()) fx = true;
		if (set.find(A[i]+Y) != set.end()) fy = true;
	}
	if (fx && fy) {
		puts("0");
		return 0;
	}
	if (!fx && fy) {
		printf("1\n%d\n",X);
		return 0;
	}
	if (fx && !fy) {
		printf("1\n%d\n",Y);
		return 0;
	}
	for (int i = 0; i < n; ++ i) {
		int p = A[i]+X;
		if (p < L) {
			if (set.find(p-Y)!=set.end() || set.find(p+Y)!=set.end()) {
				printf("1\n%d\n",p);
				return 0;
			}
		}
		p = A[i]-X;
		if (p > 0) {
			if (set.find(p-Y)!=set.end() || set.find(p+Y)!=set.end()) {
				printf("1\n%d\n",p);
				return 0;
			}
		}
		p = A[i]+Y;
		if (p < L) {
			if (set.find(p-X)!=set.end() || set.find(p+X)!=set.end()) {
				printf("1\n%d\n",p);
				return 0;
			}
		}
		p = A[i]-Y;
		if (p > 0) {
			if (set.find(p-X)!=set.end() || set.find(p+X)!=set.end()) {
				printf("1\n%d\n",p);
				return 0;
			}
		}
	}
	printf("2\n%d %d\n",X,Y);
	return 0;
}
