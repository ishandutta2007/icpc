#include <bits/stdc++.h>

const int INF = 0x3f3f3f3f;

template<int N>
struct CostFlow {
    int head[N],etot,dis[N],que[N],qf,qe,prevv[N],preve[N];
    bool inq[N];
    struct Edge {
        int v,next,cap,cost;
    } g[500000 + 5];

    void init() {
        memset(head,-1,sizeof(head)); etot = 0;
    }

    void add_edge(int u,int v,int cap,int cost) {
        g[etot] = {v,head[u],cap,cost}; head[u] = etot ++;
        g[etot] = {u,head[v],0,-cost}; head[v] = etot ++;
    }

    void mcmf(int s,int t,int &cost,int &flow) {
        cost = flow = 0;
        while (true) {
            std::fill(dis,dis + N,INF);
            dis[s] = 0;
            qf = qe = 0;
            que[qe++] = s;
            while (qf != qe) {
                int u = que[qf++];
                if (qf == N) qf = 0;
                inq[u] = false;
                for (int i = head[u]; i != -1; i = g[i].next) {
                    Edge &e = g[i];
                    if (e.cap > 0 && dis[e.v] > dis[u] + e.cost) {
                        dis[e.v] = dis[u] + e.cost;
                        prevv[e.v] = u;
                        preve[e.v] = i;
                        if (!inq[e.v]) {
                            inq[e.v] = true;
                            que[qe++] = e.v;
                            if (qe == N) qe = 0;
                        }
                    }
                }
            }
            if (dis[t] == INF) break;
            int f = INF;
            for (int u = t; u != s; u = prevv[u]) {
                f = std::min(f,g[preve[u]].cap);
            }
            cost += f * dis[t];
            flow += f;
            for (int u = t; u != s; u = prevv[u]) {
                g[preve[u]].cap -= f;
                g[preve[u] ^ 1].cap += f;
            }
        }
    }
};

CostFlow<100 + 2> F;
int n,m;

int main() {
    while (scanf("%d%d",&n,&m) == 2) {
        F.init();
        int _s = n,_t = _s + 1;
        int need = 0;
        for (int i = 0; i < n; ++ i) {
            int a,b;
            scanf("%d%d",&a,&b);
            F.add_edge(_s,i,a,0);
            F.add_edge(i,_t,b,0);
            need += b;
        }
        for (int i = 0; i < m; ++ i) {
            int a,b;
            scanf("%d%d",&a,&b); a --; b --;
            F.add_edge(a,b,INF,1);
            F.add_edge(b,a,INF,1);
        }
        int cost,flow;
        F.mcmf(_s,_t,cost,flow);
        if (flow != need) {
            puts("-1");
        } else {
            printf("%d\n",cost);
        }
    }
}

