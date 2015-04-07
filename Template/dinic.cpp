template<int N,typename T> 
struct MaxFlow {
    int s,t,head[N],etot,que[N],qf,qe,dis[N],cur[N];
    struct Edge {int v,next; T cap;}g[501000];
    void init() {
        memset(head,-1,sizeof(head)); etot = 0;
    }
    void add_edge(int u,int v,T cap) {
        g[etot].v = v; g[etot].next = head[u]; g[etot].cap = cap; head[u] = etot ++;
        g[etot].v = u; g[etot].next = head[v]; g[etot].cap = 0; head[v] = etot ++;
    }
    bool bfs() {
        memset(dis,-1,sizeof(dis));
        memcpy(cur,head,sizeof(cur));
        dis[t] = N;
        qf = qe = 0;
        que[qe++] = t;
        while (qf!=qe) {
            int u = que[qf++];
            for (int i = head[u]; i != -1; i = g[i].next) {
                Edge &e = g[i];
                if (g[i^1].cap && dis[e.v]==-1) {
                    dis[e.v] = dis[u] - 1;
                    que[qe++] = e.v;
                }
            }
        }
        return dis[s] != -1;
    }
    T dfs(int u,T a) {
        if (u==t) return a;
        T flow = 0,f;
        for (int &i = cur[u]; i != -1; i = g[i].next) {
            Edge &e = g[i];
            if (e.cap && dis[e.v]>dis[u]) {
                f = dfs(e.v,std::min(a,e.cap));
                flow += f;
                e.cap -= f;
                g[i^1].cap += f;
                a -= f;
                if (a==0) break;
            }
        }
        if (flow==0) dis[u] = -1;
        return flow;
    }
    T dinic(int _s,int _t) {
        s = _s; t = _t;
        T flow = 0;
        while (bfs()) flow += dfs(s,(T)1e30);
        return flow;
    }
};
