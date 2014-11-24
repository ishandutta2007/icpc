/* Created Time: Saturday, November 16, 2013 PM08:44:19 CST */
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <vector>
using namespace std;
const int N = 55;
const int INF = 0x3f3f3f3f;
int n,K;
struct edge {
    int v,cap,cost,rev;
    edge(){}
    edge(int v,int cap,int cost,int rev):
        v(v),cap(cap),cost(cost),rev(rev){}
};
vector <edge> g[N];
int dis[N],prevv[N],preve[N],cnt;
void add_edge(int u,int v,int cap,int cost) {
    g[u].push_back(edge(v,cap,cost,g[v].size()));
    g[v].push_back(edge(u,0,-cost,g[u].size()-1));
}
int min_cost_flow(int s,int t) {
    int flow = 0;
    if (!cnt) return 0;
    while (K>=0) {
        bool fresh = true;
        memset(dis,INF,sizeof(dis));
        dis[s] = 0;
        while (fresh) {
            fresh = false;
            for (int u = 0; u < n; u ++) 
                if (dis[u]!=INF)
                    for (int i = 0; i < g[u].size(); i ++) {
                        edge &e = g[u][i];
                        if (e.cap>0 && dis[e.v]>dis[u]+e.cost) {
                            dis[e.v] = dis[u]+e.cost;
                            prevv[e.v] = u;
                            preve[e.v] = i;
                            fresh = true;
                        }
                    }
        }

        int d = INF;
        for (int v = t; v != s; v = prevv[v]) {
            d = min(d,g[prevv[v]][preve[v]].cap);
        }
        if (dis[t]>0) 
            d = min(d,K/dis[t]);
        flow += d;
        K -= d*dis[t];
        if (K<dis[t]) return flow;
        for (int v = t; v != s; v = prevv[v]) {
            edge &e = g[prevv[v]][preve[v]];
            e.cap -= d;
            g[v][e.rev].cap += d;
        }
    }
    return flow;
}
int main() {
    scanf("%d%d",&n,&K);
    for (int i = 0; i < n; i ++)
        for (int j = 0; j < n; j ++) {
            int d;
            scanf("%d",&d);
            if (d) {
                cnt ++;
                add_edge(i,j,d,0);
                add_edge(i,j,K,1);
            }
        }
    printf("%d\n",min_cost_flow(0,n-1));
    return 0;
}