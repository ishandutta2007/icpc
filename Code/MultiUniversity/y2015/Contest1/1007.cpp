#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <queue>
#include <vector>

template<int N>
struct MaxFlow {
    int s,t,head[N],etot,cur[N],que[N],qf,qe;
    int dis[N];
    struct Edge {
        int v,next,cap;
    } g[500000 + 5];

    void init() {
        memset(head,-1,sizeof(head)); etot = 0;
    }

    void add_edge(int u,int v,int cap) {
        g[etot].v = v; g[etot].cap = cap; g[etot].next = head[u]; head[u] = etot ++;
        g[etot].v = u; g[etot].cap = 0; g[etot].next = head[v]; head[v] = etot ++;
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
        while (bfs()) flow += dfs(s,(int)1e30);
        return flow;
    }
};

const int N = 2000 + 5;
const int INF = 0x3f3f3f3f;
MaxFlow<2000> F;
int A[60000],B[60000],L[60000];
std::vector<std::pair<int,int> > edges[N];

int n,m;
int dis[N];

void work() {
    if (n <= 1) {
        printf("%d %d\n",0,0);
        return ;
    }
    for (int i = 0; i < m; ++ i) {
        edges[A[i]].push_back(std::make_pair(B[i],L[i]));
        edges[B[i]].push_back(std::make_pair(A[i],L[i]));
    }
    std::priority_queue<std::pair<int,int>,std::vector<std::pair<int,int> >,
        std::greater<std::pair<int,int> > > que;
    for (int i = 0; i < n; ++ i) {
        dis[i] = INF;
    }
    dis[0] = 0;
    que.push(std::make_pair(0,0));
    while (!que.empty()) {
        int u = que.top().second;
        int tmp = que.top().first;
        que.pop();
        if (tmp != dis[u]) continue;
        for (int i = 0; i < edges[u].size(); ++ i) {
            int v = edges[u][i].first;
            int w = edges[u][i].second;
            if (dis[v] > dis[u] + w) {
                dis[v] = dis[u] + w;
                que.push(std::make_pair(dis[v],v));
            }
        }
    }
    F.init();
    for (int i = 0; i < m; ++ i) {
        int a = A[i];
        int b = B[i];
        int w = L[i];
        if (dis[a] + w == dis[b]) {
            F.add_edge(a,b,1);
        } else if (dis[b] + w == dis[a]) {
            F.add_edge(b,a,1);
        }
    }
    printf("%d ",F.dinic(0,n - 1));
    for (int i = 0; i < n; ++ i) {
        dis[i] = INF;
    }
    dis[0] = 0;
    std::queue<int> q2;
    q2.push(0);
    while (!q2.empty()) {
        int u = q2.front(); q2.pop();
        for (int i = F.head[u]; i != - 1; i = F.g[i].next) {
            int v = F.g[i].v;
            if (dis[v] == INF) {
                dis[v] = dis[u] + 1;
                q2.push(v);
            }
        }
    }
    printf("%d\n",m - dis[n - 1]);
}

int main() {
    while (scanf("%d%d",&n,&m) == 2) {
        for (int i = 0; i < n; ++ i) {
            edges[i].clear();
        }
        for (int i = 0; i < m; ++ i) {
            scanf("%d%d%d",A + i,B + i,L + i);
            A[i] --;
            B[i] --;
        }
        work();
    }
}
