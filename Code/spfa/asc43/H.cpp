#include <bits/stdc++.h>
using LL = long long ;

const LL Inf = (LL)1e16;

template<int N,typename T>
struct MaxFlow {
    int s,t,head[N],etot,cur[N],dis[N],que[N],qf,qe;
    struct Edge {
        int v,next;
        T cap;
    } g[500000 + 5];

    void init() {
        memset(head,-1,sizeof(head)); etot = 0;
    }

    void add_edge(int u,int v,T cap) {
        g[etot] = {v,head[u],cap}; head[u] = etot ++;
        g[etot] = {u,head[v],0}; head[v] = etot ++;
    }

    bool bfs() {
        memset(dis,-1,sizeof(dis));
        memcpy(cur,head,sizeof(cur));
        dis[t] = N;
        qf = qe = 0;
        que[qe++] = t;
        while (qf != qe) {
            int u = que[qf++];
            for (int i = head[u]; i != -1; i = g[i].next) {
                int v = g[i].v;
                if (g[i ^ 1].cap && dis[v] == -1) {
                    dis[v] = dis[u] - 1;
                    que[qe++] = v;
                }
            }
        }
        return dis[s] != -1;
    }

    T dfs(int u,T a) {
        if (u == t) return a;
        T flow = 0,f;
        for (int &i = cur[u]; i != -1; i = g[i].next) {
            Edge &e = g[i];
            if (e.cap && dis[e.v] > dis[u]) {
                f = dfs(e.v,std::min(a,e.cap));
                flow += f;
                e.cap -= f;
                a -= f;
                g[i ^ 1].cap += f;
                if (a == 0) break;
            }
        }
        if (flow == 0) dis[u] = -1;
        return flow;
    }

    T dinic(int _s,int _t) {
        s = _s; t = _t;
        T flow = 0;
        while (bfs()) flow += dfs(s,(T)1e30);
        return flow;
    }
};

MaxFlow<100 + 2,LL> F;
int n;
bool vis[100 + 2];

void get_cut(int u) {
    vis[u] = true;
    for (int i = F.head[u]; i != -1; i = F.g[i].next) {
        int v = F.g[i].v;
        if (F.g[i].cap && !vis[v]) {
            get_cut(v);
        }
    }
}

int main() {
    freopen("hentium.in","r",stdin);
    freopen("hentium.out","w",stdout);
    while (scanf("%d",&n) == 1) {
        if (n == 0) break;
        F.init();
        int _s = n,_t = _s + 1;
        LL cost = 0;
        for (int i = 0; i < n; ++ i) {
            int a,b;
            scanf("%d%d",&a,&b);
            if (a < b) {
                cost += a;
                F.add_edge(_s,i,b - a);
            } else {
                cost += b;
                F.add_edge(i,_t,a - b);
            }
        }
        for (int i = 0; i < n; ++ i) {
            for (int j = 0; j < n; ++ j) {
                int x;
                scanf("%d",&x);
                if (i < j) {
                    F.add_edge(i,j,x);
                    F.add_edge(j,i,x);
                }
            }
        }
        printf("%I64d\n",F.dinic(_s,_t) + cost);
        memset(vis,0,sizeof(vis));
        get_cut(_s);
        for (int i = 0; i < n; ++ i) {
            if (i) putchar(' ');
            printf("%d",vis[i] ? 1 : 2);
        }
        puts("");
    }
}
