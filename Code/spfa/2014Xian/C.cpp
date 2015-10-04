#include <bits/stdc++.h>

const int N = 100 + 5;

template<int N,typename T>
struct MaxFlow {
    int s,t,head[N],etot,cur[N],que[N],dis[N];
    struct Edge {
        int v,next;
        T cap;
    } g[1000000 + 1];

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
        int qf = 0,qe = 0;
        que[qe++] = t;
        while (qf != qe) {
            int u = que[qf ++];
            for (int i = head[u]; i != -1; i = g[i].next) {
                Edge &e = g[i];
                if (g[i ^ 1].cap > 0 && dis[e.v] == -1) {
                    dis[e.v] = dis[u] - 1;
                    que[qe++] = e.v;
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
            if (e.cap > 0 && dis[e.v] > dis[u]) {
                f = dfs(e.v,std::min(a,e.cap));
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

    T dinic(int _s,int _t) {
        s = _s; t = _t;
        T flow = 0;
        while (bfs()) flow += dfs(s,(T)1e30);
        return flow;
    }
};

int n,A[N],graph[N][N];
MaxFlow<100 + 2,double> F;

double solve(double slop) {
    F.init();
    double sum = 0;
    int _s = n,_t = _s + 1;
    for (int i = 0; i < n; ++ i) {
        F.add_edge(_s,i,slop);
        double t = 0;
        for (int j = 0; j < n; ++ j) {
            t += graph[j][i];
        }
        F.add_edge(i,_t,t);
    }
    for (int i = 0; i < n; ++ i) {
        for (int j = 0; j < n; ++ j) {
            if (i == j || !graph[i][j]) continue;
            sum += graph[i][j];
            F.add_edge(i,j,graph[i][j]);
        }
    }
    return sum - F.dinic(_s,_t);
}

double work() {
    for (int i = 0; i < n; ++ i) {
        for (int j = i + 1; j < n; ++ j) {
            graph[i][j] = A[i] > A[j];
        }
    }
    double l = 0,r = n * n;
    for (int step = 100; step > 0; -- step) {
        double mid = (l + r) / 2;
        if (solve(mid) > 0) {
            l = mid;
        } else {
            r = mid;
        }
    }
    return r;
}

int main() {
    int cas,ca = 0;
    scanf("%d",&cas);
    while (cas--) {
        scanf("%d",&n);
        for (int i = 0; i < n; ++ i) {
            scanf("%d",A + i);
        }
        printf("Case #%d: %.10f\n",++ca,work());
    }
}
