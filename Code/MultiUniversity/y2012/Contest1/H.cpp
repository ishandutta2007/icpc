#include <bits/stdc++.h>
typedef long long LL;

template<int N>
struct MaxFlow {
    int s,t,head[N],etot,cur[N],que[N],qf,qe,dis[N];
    struct Edge {
        int v,next,cap;
    } g[3000000];

    void init() {
        memset(head,-1,sizeof(head)); etot = 0;
    }

    void add_edge(int u,int v,int cap) {
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

    int dfs(int u,int a) {
        if (u == t) return a;
        int flow = 0,f;
        for (int &i = cur[u]; i != -1; i = g[i].next) {
            Edge &e = g[i];
            if (e.cap && dis[e.v] > dis[u]) {
                f = dfs(e.v,std::min(e.cap,a));
                e.cap -= f;
                g[i ^ 1].cap += f;
                a -= f;
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
        while (bfs()) flow += dfs(s,(int)1e30);
        return flow;
    }
};

MaxFlow<1000 + 2> F;

const int N = 1000 + 5;
int B[N][N],C[N];
int n;

inline void read(int &x) {
    char c;
    for (c = getchar(); c < '0' || c > '9'; c = getchar());
    for (x = 0; c >= '0' && c <= '9'; c = getchar()) x = x * 10 + c - '0';
}

int main() {
    int cas;
    read(cas);
    while (cas--) {
        read(n);
        int sum = 0;
        F.init();
        int _s = n,_t = n + 1;
        for (int i = 0; i < n; ++ i) {
            for (int j = 0; j < n; ++ j) {
                read(B[i][j]);
                F.add_edge(i,j,B[i][j]);
                sum += B[i][j];
            }
        }
        for (int j = 0; j < n; ++ j) {
            int s = 0;
            for (int i = 0; i < n; ++ i) {
                s += B[i][j];
            }
            F.add_edge(j,_t,s);
        }
        for (int i = 0; i < n; ++ i) {
            read(C[i]);
            F.add_edge(_s,i,C[i]);
        }
        printf("%d\n",sum - F.dinic(_s,_t));
    }
}
