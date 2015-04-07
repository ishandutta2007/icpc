const int INF = 0x3f3f3f3f;
template<int N> struct CostFlow {
    int s,t,vis[N],d[N],head[N],cur[N],etot;
    struct Edge {int v,cap,cost,next;} g[555555];
    void add_edge(int u,int v,int cap,int cost) {
        g[etot].v = v; g[etot].cap = cap; g[etot].cost = cost; g[etot].next = head[u]; head[u] = etot ++;
        g[etot].v = u; g[etot].cap = 0; g[etot].cost = -cost; g[etot].next = head[v]; head[v] = etot ++;
    }
    void init() {
        memset(head,-1,sizeof(head)); etot = 0;
    }
    int aug(int u,int a) {
        if (u==t) return a;
        vis[u] = 1;
        int flow = 0,f;
        for (int &i = cur[u]; i != -1; i = g[i].next) {
            Edge &e = g[i];
            if (e.cap && !vis[e.v] && d[u]==d[e.v]+e.cost)
                if (f = aug(e.v,min(a,e.cap))) {
                    flow += f;
                    e.cap -= f;
                    g[i^1].cap += f;
                    a -= f;
                    if (a==0) break;
                }
        }
        return flow;
    }
    bool modlabel() {
        int tmp = INF;
        for (int u = 0; u < N; u ++) if (vis[u]) {
            for (int i = head[u]; i != -1; i = g[i].next) {
                Edge &e = g[i];
                if (e.cap && !vis[e.v])
                    tmp = min(tmp,d[e.v]+e.cost-d[u]);
            }
        }
        if (tmp==INF) return true;
        for (int u = 0; u < N; u ++) if (vis[u]) {
            vis[u] = 0;
            d[u] += tmp;
        }
        return false;
    }
    void mcmf(int _s,int _t,int &cost,int &flow) {
        s = _s; t = _t; cost = flow = 0; int f;
        memset(d,0,sizeof(d));
        while (true) {
            memcpy(cur,head,sizeof(head));
            while (f=aug(s,INF)) {
                flow += f;
                cost += f*d[s];
                memset(vis,0,sizeof(vis));
            }
            if (modlabel()) break;
        }
    }
};
