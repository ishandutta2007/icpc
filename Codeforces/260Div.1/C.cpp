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

typedef long long lld;
const int N = 301000;
int dis[N][2],from[N][2],dsu[N],n,m,nq,dep[N],mx[N][2];
vector<int> G[N];
int Find(int x) { return dsu[x]==x ? x : dsu[x] = Find(dsu[x]); }
vector<int> Stack;
bool vis[N];

void dfs(int u,int fa) {
	vis[u] = true;
	Stack.pb(u);
	dis[u][0] = dis[u][1] = -1;
	from[u][0] = from[u][1] = -1;
	snuke(it,G[u]) {
		int v = *it;
		if (v==fa) continue;
		dfs(v,u);
		if (dis[v][0] > dis[u][1]) {
			dis[u][1] = dis[v][0];
			from[u][1] = v;
			if (dis[u][0] < dis[u][1]) {
				swap(dis[u][0],dis[u][1]);
				swap(from[u][0],from[u][1]);
			}
		}
	}
	dis[u][0] ++;
	dis[u][1] ++;
}

void DFS(int u,int fa,int val) {
	mx[u][0] = dis[u][0];
	mx[u][1] = dis[u][1];
	if (val > mx[u][1]) {
		mx[u][1] = val;
		if (mx[u][1] > mx[u][0]) {
			swap(mx[u][1],mx[u][0]);
		}
	}
	//printf("u=%d,dis[0] = %d,dis[1] = %d,val = %d\n",u,dis[u][0],dis[u][1],val);
	//printf("u=%d,mx[0] = %d,mx[1] = %d,val = %d\n",u,mx[u][0],mx[u][1],val);
	snuke(it,G[u]) {
		int v = *it;
		if (v==fa) continue;
		int tmp = val + 1;
		if (from[u][0]==v) {
			tmp = max(tmp,dis[u][1] + 1);
		} else {
			tmp = max(tmp,dis[u][0] + 1);
		}
		DFS(v,u,tmp);
	}
}

void prepare() {
	for (int i = 1; i <= n; ++ i) {
		if (!vis[i]) {
			Stack.clear();
			dfs(i,-1);
			DFS(i,-1,0);
			int vmax[2] = {-1,-1},p = -1;
			snuke(it,Stack) {
				int v = *it;
				int a = mx[v][0] + mx[v][1];
				int b = vmax[0] + vmax[1];
				if (a>b || a==b && mx[v][0]<vmax[0]) {
					p = v;
					vmax[0] = mx[v][0];
					vmax[1] = mx[v][1];
				}
			}
			snuke(it,Stack) {
				dsu[*it] = p;
			}
		}
	}
}

int main() {
	scanf("%d%d%d",&n,&m,&nq);
	for (int i = 1; i <= n; ++ i) {
		dsu[i] = i;
	}
	for (int i = 0; i < m; ++ i) {
		int a,b;
		scanf("%d%d",&a,&b);
		G[a].pb(b);
		G[b].pb(a);
	}
	prepare();
	/* for (int i = 1; i <= n; ++ i) {
	   printf("dsu[i] = %d\n",Find(i));
	   }*/
	/*for (int i = 1; i <= n; ++ i) {
	  printf("%d %d\n",mx[i][0],mx[i][1]);
	  }*/
	while (nq--) {
		int op,a,b;
		scanf("%d",&op);
		if (op==1) {
			scanf("%d",&a);
			int x = Find(a);
			printf("%d\n",mx[x][0] + mx[x][1]);
		} else {
			scanf("%d%d",&a,&b);
			a = Find(a);
			b = Find(b);
			//  puts("fuck");
			if (a==b) continue;
			int tmp[2][2];
			tmp[0][0] = mx[a][0];
			tmp[0][1] = mx[a][1];
			int val = max(mx[b][0],mx[b][1]) + 1;
			if (val > tmp[0][1]) {
				tmp[0][1] = val;
				if (tmp[0][1] > tmp[0][0]) {
					swap(tmp[0][1],tmp[0][0]);
				}
			}
			tmp[1][0] = mx[b][0];
			tmp[1][1] = mx[b][1];
			val = max(mx[a][0],mx[a][1]) + 1;
			if (val > tmp[1][1]) {
				tmp[1][1] = val;
				if (tmp[1][1] > tmp[1][0]) {
					swap(tmp[1][1],tmp[1][0]);
				}
			}
			int xx = tmp[0][0] + tmp[0][1];
			int yy = tmp[1][0] + tmp[1][1];
			//printf("a = %d,xx = %d\n,b = %d,yy = %d\n",a,xx,b,yy);
			if (xx>yy || xx==yy && tmp[0][0] < tmp[1][0]) {
				dsu[b] = a;
				mx[a][0] = tmp[0][0];
				mx[a][1] = tmp[0][1];
			} else {
				dsu[a] = b;
				mx[b][0] = tmp[1][0];
				mx[b][1] = tmp[1][1];
			}
			// a = Find(a);
			// printf("show::%d %d\n",mx[a][0],mx[a][1]);
		}
	}

	return 0;
}

