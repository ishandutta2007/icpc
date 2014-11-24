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

const int N = 101000;

int ch[N][26];
bool state[N][2][2];
int n,m,tot,que[N],qe;
char str[N];

void insert(char *str) {
	int cur = 0;
	for ( ; *str; ++ str) {
		int c = (*str) - 'a';
		if (ch[cur][c]==0) ch[cur][c] = tot ++;
		cur = ch[cur][c];
	}
}

bool check() {
	bool fuck[2][2];
	for (int i = 0; i < 2; ++ i)
		for (int j = 0; j < 2; ++ j)
			fuck[i][j] = state[0][i][j];
	if (m==1) {
		return fuck[1][1];
	}
	fuck[0][0] ^= 1;
	if (fuck[0][0] && fuck[1][1]) {
		return true;
	} else if (fuck[0][0] && !fuck[1][1]) {
		return false;
	} else if (!fuck[0][0] && fuck[1][1]) {
		return m&1;
	} else {
		return false;
	}
}

int main() {
	scanf("%d%d",&n,&m);
	tot ++;
	for (int i = 0; i < n; ++ i) {
		scanf("%s",str);
		insert(str);
	}
	que[qe++] = 0;
	for (int qf = 0; qf != qe; ++ qf) {
		int u = que[qf];
		for (int i = 0; i < 26; ++ i) {
			if (ch[u][i]) {
				que[qe++] = ch[u][i];
			}
		}
	}
	for (int I = qe-1; I >= 0; -- I) {
		int u = que[I];
		int cnt = 0;
		for (int i = 0; i < 26; ++ i) {
			cnt += ch[u][i]!=0;
		}
		if (cnt==0) {
			state[u][0][0] = state[u][0][1] = state[u][1][0] = state[u][1][1] = false;
			continue;
		}
		for (int i = 0; i < 26; ++ i) {
			int v = ch[u][i];
			if (v==0) continue;
			// 1,0
			state[u][1][0] |= state[v][0][1]==false;
			// 1,1
			state[u][1][1] |= state[v][1][1]==false;
			// 0,0
			state[u][0][0] |= state[v][0][0]==true;
			// 0,1
			state[u][0][1] |= state[v][1][0]==true;
		}
		state[u][0][0] ^= 1;
		state[u][0][1] ^= 1;
	}
	puts(check() ? "First" : "Second");
	return 0;
}

