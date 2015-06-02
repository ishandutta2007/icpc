template<int N,typename T> 
struct CostFlow {
    int s,t,head[N],etot,prevv[N],preve[N],inq[N],que[N],qf,qe;
    T dis[N];
    struct Edge {int v,next; T cap,cost;} g[501000];
    void init() {
        memset(head,-1,sizeof(head)); etot = 0;
    }
    void add_edge(int u,int v,T cap,T cost) {
        g[etot].v = v; g[etot].cap = cap; g[etot].cost = cost; g[etot].next = head[u]; head[u] = etot ++;
        g[etot].v = u; g[etot].cap = 0; g[etot].cost = -cost; g[etot].next = head[v]; head[v] = etot ++;
    }
    void mcmf(int _s,int _t,T &cost,T &flow) {
        s = _s; t = _t; cost = flow = 0;
        while (true) {
            for (int i = 0; i < N; i ++) dis[i] = (T)1e30;
            dis[s] = 0;
            qf = qe = 0;
            que[qe++] = s;
            while (qf!=qe) {
                int u = que[qf++]; inq[u] = 0; if (qf==N) qf = 0;
                for (int i = head[u]; i != -1; i = g[i].next) {
                    Edge &e = g[i];
                    if (e.cap && dis[e.v]>dis[u]+e.cost) {
                        dis[e.v] = dis[u]+e.cost;
                        prevv[e.v] = u; preve[e.v] = i;
                        if (!inq[e.v]) {
                            que[qe++] = e.v;
                            if (qe==N) qe = 0;
                            inq[e.v] = 1;
                        }
                    }
                }
            }
            if (dis[t]==T(1e30)) break;
            T f = (T)1e30;
            for (int u = t; u != s; u = prevv[u])
                f = std::min(f,g[preve[u]].cap);
            cost += f*dis[t];
            flow += f;
            for (int u = t; u != s; u = prevv[u])
                g[preve[u]].cap -= f,g[preve[u]^1].cap += f;
        }
    }
};
