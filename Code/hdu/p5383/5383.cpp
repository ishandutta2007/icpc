#include <bits/stdc++.h>

const int INF = 0x3f3f3f3f;

template<int N>
struct CostFlow {
    int head[N],etot,que[N],prevv[N],preve[N],dis[N];
    bool inq[N];
    struct Edge {
        int v,cap,cost,next;
    } g[1000000 + 5];

    void init() {
        memset(head,-1,sizeof(head)); etot = 0;
    }

    void add_edge(int u,int v,int cap,int cost) {
        g[etot] = {v,cap,cost,head[u]}; head[u] = etot ++;
        g[etot] = {u,0,-cost,head[v]}; head[v] = etot ++;
    }

    void mcmf(int s,int t,int &flow,int &cost) {
        flow = cost = 0;
        while (true) {
            memset(dis,INF,sizeof(dis));
            dis[s] = 0;
            int qf = 0,qe = 0;
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
                            que[qe++] = e.v;
                            if (qe == N) qe = 0;
                            inq[e.v] = true;
                        }
                    }
                }
            }
            if (dis[t] >= 0) break;
            int f = INF;
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

CostFlow<300 + 2> F;
const int N = 300 + 5;
int n,m;
int T[N],L[N],A[N];
int l[N],a[N],r[N],s[N][2];

bool check(int i,int j,int k) {
    if (L[i] + L[j] != l[k]) return false;
    for (int t = 0; t < r[k]; ++ t) {
        if (s[k][t] != i && s[k][t] != j) return false;
    }
    return true;
}

int work() {
    F.init();
    int _s = n,_t = _s + 1;
    int sum = 0;
    for (int i = 0; i < n; ++ i) {
        sum += A[i];
        if (T[i] == 1) {
            F.add_edge(i,_t,1,0);
        } else {
            F.add_edge(_s,i,1,0);
            for (int j = 0; j < n; ++ j) {
                if (T[j] == 0) continue;
                int val = 0;
                for (int k = 0; k < m; ++ k) {
                    if (check(i,j,k)) {
                        val = std::max(val,a[k] - A[i] - A[j]);
                    }
                }
                if (val > 0)
                    F.add_edge(i,j,1,-val);
            }
        }
    }
    int flow,cost;
    F.mcmf(_s,_t,flow,cost);
    return sum - cost;
}

int main() {
    int cas;
    scanf("%d",&cas);
    while (cas--) {
        scanf("%d%d",&n,&m);
        for (int i = 0; i < n; ++ i) {
            scanf("%d%d%d",T + i,L + i,A + i);
        }
        for (int i = 0; i < m; ++ i) {
            scanf("%d%d%d",l + i,a + i,r + i);
            for (int j = 0; j < r[i]; ++ j) {
                scanf("%d",&s[i][j]); s[i][j] --;
            }
        }
        printf("%d\n",work());
    }
}
