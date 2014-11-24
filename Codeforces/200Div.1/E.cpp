#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <queue>
using namespace std;
const int N = 222,INF = 0x3f3f3f3f;
struct MaxFlow {
        int s,t,dis[N],cur[N],head[N],etot,que[N],qf,qe;
        struct edge {int v,cap,next;}g[2222];
        void init() {
                memset(head,-1,sizeof(head)); etot = 0;
        }
        void add_edge(int u,int v,int cap) {
                g[etot] = (edge) {v,cap,head[u]}; head[u] = etot ++;
                g[etot] = (edge) {u,cap,head[v]}; head[v] = etot ++;
        }
        bool bfs() {
                for (int i = 0; i < N; i ++) cur[i] = head[i], dis[i] = INF;
                dis[s] = 0;
                qf = qe = 0;
                que[qe++] = s;
                while (qf<qe) {
                        int u = que[qf++];
                        for (int i = head[u]; i != -1; i = g[i].next) {
                                edge &e = g[i];
                                if (dis[e.v]==INF && e.cap) {
                                        dis[e.v] = dis[u]+1;
                                        que[qe++] = e.v;
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
                        if (dis[e.v]>dis[u] && e.cap) {
                                f = dfs(e.v,min(a,e.cap));
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
                while (bfs()) flow += dfs(s,INF);
                return flow;
        }
}F;
int n,m,p[N],vis[N],tree[N][N];
void remark(int u) {
        vis[u] = 1;
        for (int i = F.head[u]; i != -1; i = F.g[i].next) {
                MaxFlow::edge &e = F.g[i];
                if (e.cap && !vis[e.v]) remark(e.v);
        }
}
void work() {
        int salary = 0;
        for (int i = 1; i <= n; i ++) p[i] = 1;
        for (int i = 2; i <= n; i ++) {
                for (int j = 0; j < m<<1; j += 2)
                        F.g[j].cap = F.g[j].cap+F.g[j^1].cap>>1,F.g[j^1].cap = F.g[j].cap;
                int flow = F.dinic(i,p[i]);
                memset(vis,0,sizeof(vis));
                remark(i);
                for (int j = i+1; j <= n; j ++) 
                        if (vis[j] && p[j]==p[i]) p[j] = i;
                tree[p[i]][i] = flow;
                salary += flow;
        }
        printf("%d\n",salary);
        printf("%d",1);
        priority_queue<pair<int,int> > que;
        for (int i = 1; i <= n; i ++) if (tree[1][i]) que.push(make_pair(tree[1][i],i));
        while (!que.empty()) {
                int u = que.top().second; que.pop();
                printf(" %d",u);
                for (int i = 1; i <= n; i ++) 
                        if (tree[u][i]) que.push(make_pair(tree[u][i],i));
        }
        printf("\n");
}
int main() {
        scanf("%d%d",&n,&m);
        F.init();
        for (int i = 0; i < m; i ++) {
                int a,b,c;
                scanf("%d%d%d",&a,&b,&c); 
                F.add_edge(a,b,c);
        }
        work();
        return 0;
}
