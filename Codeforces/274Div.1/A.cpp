#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <vector>

const int N = 100000 + 5;
int n;
std::pair<int,int> date[N];

int main() {
	scanf("%d",&n);
	for (int i = 0; i < n; ++ i) {
		scanf("%d%d",&date[i].first,&date[i].second);
	}
	std::sort(date,date+n);
	int day = 0;
	for (int i = 0; i < n; ++ i) {
		if (date[i].second >= day) {
			day = date[i].second;
		} else {
			day = date[i].first;
		}
	}
	printf("%d\n",day);
	return 0;
}
