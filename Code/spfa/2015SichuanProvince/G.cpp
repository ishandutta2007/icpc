#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <vector>

template<int N>
struct MaxFlow {
    int s,t,head[N],etot,cur[N],que[N],qf,qe,dis[N];
    struct Edge {
        int v,next,cap;
    } g[500000];

    void init() {
        memset(head,-1,sizeof(head)); etot = 0;
    }

    void add_edge(int u,int v,int cap) {
        g[etot].v = v; g[etot].next = head[u]; g[etot].cap = cap;
        head[u] = etot ++;
        g[etot].v = u; g[etot].next = head[v]; g[etot].cap = 0;
        head[v] = etot ++;
    }

    bool bfs() {
        qf = qe = 0;
        memset(dis,-1,sizeof(dis));
        dis[t] = N;
        memcpy(cur,head,sizeof(cur));
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

    int dfs(int u,int a) {
        if (u == t) return a;
        int flow = 0,f;
        for (int &i = cur[u]; i != -1; i = g[i].next) {
            Edge &e = g[i];
            if (e.cap && dis[e.v] > dis[u]) {
                f = dfs(e.v,std::min(a,e.cap));
                a -= f;
                e.cap -= f;
                g[i ^ 1].cap += f;
                flow += f;
                if (a == 0) break;
            }
        }
        if (flow == 0) dis[u] = -1;
        return flow;
    }

    int dinic(int _s,int _t) {
        s = _s; t = _t;
        int flow = 0;
        while (bfs()) flow += dfs(s,(int) 1e30);
        return flow;
    }
};

const int INF = 0x3f3f3f3f;
MaxFlow<1000 * 2 + 2> F;
int W[1000],kind[1000];
std::vector<int> edges[1000];
int side[1000];
int n,m;

void dfs(int u,int s) {
    side[u] = s;
    for (int i = 0; i < edges[u].size(); ++ i) {
        int v = edges[u][i];
        if (side[v] == -1) {
            dfs(v,s ^ 1);
        }
    }
}

int work() {
    F.init();
    int _s = n + n,_t = _s + 1;
    memset(side,-1,sizeof(side));
    for (int i = 0; i < n; ++ i) {
        if (side[i] == -1) {
            dfs(i,0);
        }
    }

    for (int i = 0; i < n; ++ i) {
        if (kind[i] == 2) {
            F.add_edge(i,i + n,W[i]);
        } else if (side[i] ^ kind[i] ^ 1) {
            F.add_edge(_s,i,W[i]);
        } else {
            F.add_edge(i,_t,W[i]);
        }
    }

    for (int u = 0; u < n; ++ u) {
        if (kind[u] == 2) continue;
        if (side[u] ^ kind[u]) continue;
        for (int i = 0; i < edges[u].size(); ++ i) {
            int v = edges[u][i];
            if (kind[v] == 2) continue;
            if (kind[v] != kind[u]) continue;
            F.add_edge(u,v,INF);
        }
    }

    for (int i = 0; i < n; ++ i) {
        if (kind[i] != 2) continue;
        if (side[i] == 0) {
            for (int j = 0; j < edges[i].size(); ++ j) {
                int v = edges[i][j];
                if (kind[v] == 0) {
                    F.add_edge(i + n,v,INF);
                } else if (kind[v] == 1) {
                    F.add_edge(v,i,INF);
                } else {
                    F.add_edge(i + n,v,INF);
                }
            }
        } else {
            for (int j = 0; j < edges[i].size(); ++ j) {
                int v = edges[i][j];
                if (kind[v] == 0) {
                    F.add_edge(v,i,INF);
                } else if (kind[v] == 1) {
                    F.add_edge(i + n,v,INF);
                } else {
                    F.add_edge(i + n,v,INF);
                }
            }
        }
    }

    return F.dinic(_s,_t);
}

int main() {
    while (scanf("%d%d",&n,&m) == 2) {
        for (int i = 0; i < n; ++ i) {
            scanf("%d",W + i);
            edges[i].clear();
        }
        for (int i = 0; i < n; ++ i) {
            scanf("%d",kind + i); kind[i] --;
        }
        for (int i = 0; i < m; ++ i) {
            int a,b;
            scanf("%d%d",&a,&b); a --; b --;
            edges[a].push_back(b);
            edges[b].push_back(a);
        }
        printf("%d\n",work());
    }
}
