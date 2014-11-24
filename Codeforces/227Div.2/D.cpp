#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <queue>
using namespace std;
const int N = 1010,INF = 0x3f3f3f3f;
struct MaxFlow {
        int s,t,dis[N],cur[N],head[N],etot;
        struct edge {int v,cap,next;}g[501000];
        void add_edge(int u,int v,int cap) {
                g[etot] = (edge) {v,cap,head[u]}; head[u] = etot ++;
                g[etot] = (edge) {u,0,head[v]}; head[v] = etot ++;
        }
        void init() {
                memset(head,-1,sizeof(head)); etot = 0;
        }
        bool bfs() {
                queue<int> que;
                que.push(s);
                memset(dis,INF,sizeof(dis));
                dis[s] = 0;
                while (!que.empty()) {
                        int u = que.front(); que.pop();
                        for (int i = head[u]; i != -1; i = g[i].next) {
                                edge &e = g[i];
                                if (dis[e.v]==INF && e.cap) {
                                        dis[e.v] = dis[u]+1;
                                        que.push(e.v);
                                }
                        }
                }
                return dis[t]!=INF;
        }
        int dfs(int u,int a) {
                if (u==t) return a;
                int flow = 0,f;
                for (int &i = cur[u]; i != -1; i = g[i].next) {
                        edge &e = g[i];
                        if (dis[e.v]>dis[u] && e.cap && (f=dfs(e.v,min(a,e.cap))) ) {
                                flow += f;
                                e.cap -= f;
                                g[i^1].cap += f;
                                a -= f;
                                if (a==0) break;
                        }
                }
                return flow;
        }
        int dinic(int _s,int _t) {
                s = _s; t = _t;
                int flow = 0;
                while (bfs()) {
                        memcpy(cur,head,sizeof(head));
                        flow += dfs(s,INF);
                }
                return flow;
        }
}F;
int n,m,u[N],v[N],in[N],out[N],lop[N];
int work() {
        int ans = INF;
        for (int i = 1; i <= n; i ++) {
                int tmp = 0;
                tmp = n-in[i]+n-out[i]-(!lop[i]);
                if (tmp>=ans) continue;
                int _s = 0,_t = n*2+1;
                F.init();
                for (int j = 1; j <= n; j ++) {
                        F.add_edge(_s,j,1);
                        F.add_edge(j+n,_t,1);
                }
                int cnt = 0;
                for (int j = 0; j < m; j ++) if (u[j]!=i && v[j]!=i) {
                        F.add_edge(u[j],v[j]+n,1);
                        cnt ++;
                }
                int flow = F.dinic(_s,_t);
                tmp += cnt-flow+n-1-flow;
                if (tmp<ans) ans = tmp;
        }
        return ans;
}
int main() {
        scanf("%d%d",&n,&m);
        for (int i = 0; i < m; i ++) {
                scanf("%d%d",&u[i],&v[i]),in[v[i]] ++, out[u[i]] ++;
                if (u[i]==v[i]) lop[u[i]] = 1;
        }
        printf("%d\n",work());
        return 0;
}
