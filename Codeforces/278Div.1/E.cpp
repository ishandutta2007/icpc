#include <bits/stdc++.h>

const int INF = 0x3f3f3f3f;

template<typename T> void toMin(T &a,T b) {
	if (a > b) a = b;
}

namespace Graph {
	const int N = 100000 + 5;
	const int M = 100000 + 5;
	int W[N],n,m,nq;
	int head[N],etot,dfn[N],low[N],top,btot;
	int stack[M],belong[M];
	struct Edge {
		int v,next;
	} g[M<<1];
	bool iscut[N];
	int set[N];
	std::vector<int> edges[N+M];
	std::set<int> sets[N+M];
	bool vis[M];

	void tarjan(int u,int root,int tim) {
		dfn[u] = low[u] = tim;
		int child_count = 0;
		for (int i = head[u]; i != -1; i = g[i].next) {
			int v = g[i].v;
			if (vis[i>>1]) continue;
			vis[i>>1] = true;
			stack[top++] = i>>1;
			if (dfn[v]) {
				low[u] = std::min(low[u],dfn[v]);
				continue;
			}
			tarjan(v,root,tim+1);
			if (u != root) iscut[u] |= (low[v]>=dfn[u]);
			if (low[v]>=dfn[u] || u==root) {
				while (true) {
					int id = stack[--top];
					belong[id] = btot;
					if (id == i>>1) break;
				}
				btot ++;
			}
			low[u] = std::min(low[u],low[v]);
			child_count ++;
		}
		if (u==root && child_count>1) iscut[u] = true;
	}

	void bcc() {
		tarjan(0,0,1);
	}

	void build() {
		for (int u = 0; u < n; ++ u) {
			if (iscut[u] || head[u]==-1) {
				int id = btot ++;
				set[u] = id;
				sets[id].insert(u);
				for (int i = head[u]; i != -1; i = g[i].next) {
					int v = belong[i>>1];
					edges[id].push_back(v);
					edges[v].push_back(id);
				}
			}
		}
		for (int i = 0; i < m; ++ i) {
			int a = g[i<<1].v;
			int b = g[i<<1|1].v;
			if (!iscut[a]) {
				set[a] = belong[i];
				sets[belong[i]].insert(a);
			}
			if (!iscut[b]) {
				set[b] = belong[i];
				sets[belong[i]].insert(b);
			}
		}
		for (int i = 0; i < btot; ++ i) {
			std::sort(edges[i].begin(),edges[i].end());
			edges[i].erase(std::unique(edges[i].begin(),edges[i].end())\
					,edges[i].end());
		}
	}

	void init() {
		memset(head,-1,sizeof(head)); etot = 0;
	}

	void addEdge(int u,int v) {
		g[etot].v = v; g[etot].next = head[u]; head[u] = etot ++;
	}

	void work() {
		scanf("%d%d%d",&n,&m,&nq);
		for (int i = 0; i < n; ++ i) {
			scanf("%d",W+i);
		}
		init();
		for (int i = 0; i < m; ++ i) {
			int a,b;
			scanf("%d%d",&a,&b); a --; b --;
			addEdge(a,b);
			addEdge(b,a);
		}
		bcc();
		build();
	}
}

namespace HeavyLightDecompose{
	const int N = Graph::N+Graph::M;
	std::vector<int> *edges;
	int *weight;
	int map[N],remap[N];

	bool iscut[N];
	int hld_tot;
	int pos[N];
	int path_top[N];
	int parent[N];
	int depth[N];
	int sz[N];
	std::multiset<int> values[N];

	struct SegmentTree {
#define lson l,mid,rt<<1
#define rson mid+1,r,rt<<1|1
		int t[N<<2];
		void update(int u,int l=0,int r=hld_tot,int rt=1) {
			if (l == r) {
				t[rt] = 0;
				if (!values[u].empty())
					t[rt] = *values[u].begin();
				return ;
			}
			int mid = l+r>>1;
			if (pos[u] <= mid) update(u,lson);
			else update(u,rson);
			t[rt] = std::min(t[rt<<1],t[rt<<1|1]);
		}
		int query(int L,int R,int l=0,int r=hld_tot,int rt=1) {
			if (L<=l && r<=R) 
				return t[rt];
			int mid = l+r>>1;
			if (L<=mid && mid<R)
				return std::min(query(L,R,lson),query(L,R,rson));
			if (L <= mid)
				return query(L,R,lson);
			return query(L,R,rson);
		}
	}sgt;

	void dfs(int u,int key) {
		path_top[u] = key;
		pos[u] = hld_tot ++;
		int p = -1,mx = 0;
		for (int v : edges[u]) {
			if (v == parent[u]) continue;
			if (sz[v] > mx) {
				mx = sz[v];
				p = v;
			}
		}
		if (p != -1) dfs(p,key);
		for (int v : edges[u]) {
			if (v == parent[u]) continue;
			if (v == p) continue;
			dfs(v,v);
		}
	}

	void get_sz(int u,int fa) {
		parent[u] = fa;
		if (fa != -1)
			depth[u] = depth[fa]+1;
		sz[u] = 1;
		for (int v : edges[u]) {
			if (v == fa) continue;
			get_sz(v,u);
			sz[u] += sz[v];
		}
	}
	
	void modify(int u,int pre,int now) {
		if (iscut[u] && parent[u]!=-1) {
			modify(parent[u],pre,now);
		}
		if (pre) {
			values[u].erase(values[u].find(pre));
		}
		values[u].insert(now);
		sgt.update(u);
	}

	int query(int a,int b) {
		int ret = INF;
		while (path_top[a] != path_top[b]) {
			if (depth[path_top[a]] < depth[path_top[b]]) std::swap(a,b);
			toMin(ret,sgt.query(pos[path_top[a]],pos[a]));
			a = parent[path_top[a]];
		}
		if (depth[a] > depth[b]) std::swap(a,b);
		toMin(ret,sgt.query(pos[a],pos[b]));
		if (!iscut[a] && parent[a]!=-1)
			toMin(ret,weight[remap[parent[a]]]);
		return ret;
	}

	void work() {
		edges = Graph::edges;
		weight = Graph::W;

		for (int i = 0; i < Graph::n; ++ i) {
			map[i] = Graph::set[i];
			remap[map[i]] = i;
		}

		for (int i = 0; i < Graph::n; ++ i) 
			iscut[map[i]] = Graph::iscut[i];


		get_sz(0,-1);
		dfs(0,0);
		for (int i = 0; i < Graph::btot; ++ i) {
			for (int v : Graph::sets[i]) {
				modify(i,0,weight[v]);
			}
		}
		int nq = Graph::nq;
		while (nq --) {
			char op[2];
			int a,b;
			scanf("%s%d%d",op,&a,&b);
			if (op[0] == 'C') {
				a --;
				modify(map[a],weight[a],b);
				weight[a] = b;
			} else {
				a --; b --;
				if (a == b) {
					printf("%d\n",weight[a]);
					continue;
				}
				a = map[a];
				b = map[b];
				printf("%d\n",query(a,b));
			}
		}
	}
}

int main() {
	Graph::work();
	HeavyLightDecompose::work();
	return 0;
}
