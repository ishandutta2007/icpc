#include <bits/stdc++.h>

template<int N,typename T>
struct CostFlow {
    int head[N],etot,que[N],qf,qe,prevv[N],preve[N];
    T dis[N];
    bool inq[N];
    struct Edge {
        int v;
        T cap,cost;
        int next;
    } g[1000000 + 5];

    void init() {
        memset(head,-1,sizeof(head)); etot = 0;
    }

    void add_edge(int u,int v,T cap,T cost) {
        g[etot] = {v,cap,cost,head[u]}; head[u] = etot ++;
        g[etot] = {u,0,-cost,head[v]}; head[v] = etot ++;
    }

    void mcmf(int s,int t,T &flow,T &cost) {
        T Inf = (T)1e30;
        flow = cost = 0;
        while (true) {
            std::fill(dis,dis + N,Inf);
            dis[s] = 0;
            qf = qe = 0;
            que[qe++] = s;
            while (qf != qe) {
                int u = que[qf++];
                if (qf == N) qf = 0;
                inq[u] = false;
                for (int i = head[u]; i != -1; i = g[i].next) {
                    Edge &e = g[i];
                    if (e.cap && dis[e.v] > dis[u] + e.cost) {
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
            if (dis[t] == Inf) break;
            T f = Inf;
            for (int u = t; u != s; u = prevv[u]) {
                f = std::min(f,g[preve[u]].cap);
            }
            flow += f;
            cost += f * dis[t];
            for (int u = t; u != s; u = prevv[u]) {
                g[preve[u]].cap -= f;
                g[preve[u] ^ 1].cap += f;
            }
        }
    }
};

const int N = 50 + 5;
CostFlow<50 * 50 * 2 + 2,int> F;
int n,m;
int mat[N][N],A[N][N],B[N][N];
int dir[4][2] = {-1,0,1,0,0,-1,0,1};

int work() {
    F.init();
    int _s = n * m * 2,_t = _s + 1;
    int need = 0;
    for (int i = 0; i < n; ++ i) {
        for (int j = 0; j < m; ++ j) {
            if (mat[i][j] == 0) {
                F.add_edge(_s,i * m + j + n * m,1,0);
                F.add_edge(i * m + j,_t,1,0);
                need ++;
            } else if (mat[i][j] & 1) {
                F.add_edge(_s,i * m + j + n * m,1,0);
                need ++;
            } else {
                F.add_edge(i * m + j,_t,1,0);
            }
            for (int d = 0; d < 4; ++ d) {
                int ii = i + dir[d][0];
                int jj = j + dir[d][1];
                if (ii < 0 || ii >= n || jj < 0 || jj >= m) continue;
                int cost = d == 0 ? A[i - 1][j] : d == 1 ? A[i][j] : d == 2 ? B[i][j - 1] : B[i][j];
                F.add_edge(i * m + j + n * m,ii * m + jj,1,cost);
            }
        }
    }
    int flow,cost;
    F.mcmf(_s,_t,flow,cost);
    if (flow != need) return -1;
    return cost;
}

int main() {
    int cas,ca = 0;
    scanf("%d",&cas);
    while (cas--) {
        scanf("%d%d",&n,&m);
        for (int i = 0; i < n; ++ i) {
            for (int j = 0; j < m; ++ j) {
                scanf("%d",&mat[i][j]);
            }
        }
        for (int i = 0; i < n - 1; ++ i) {
            for (int j = 0; j < m; ++ j) {
                scanf("%d",&A[i][j]);
            }
        }
        for (int i = 0; i < n; ++ i) {
            for (int j = 0; j < m - 1; ++ j) {
                scanf("%d",&B[i][j]);
            }
        }
        printf("Case #%d: %d\n",++ca,work());
    }
}
