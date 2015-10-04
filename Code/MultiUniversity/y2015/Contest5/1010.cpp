#include <bits/stdc++.h>

template<int N>
struct MaxFlow {
    int s,t,head[N],etot,cur[N],que[N],qf,qe,dis[N];
    struct Edge {
        int v,next,cap;
    } g[1000000 + 5];

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
        que[qe++] = t;
        memset(dis,-1,sizeof(dis));
        memcpy(cur,head,sizeof(cur));
        dis[t] = N;
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
                flow += f;
                e.cap -= f;
                a -= f;
                g[i ^ 1].cap += f;
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

const int N = 200 + 5;
bool graph[N][N];
int n,m,K;

MaxFlow<200 + 2 + 500> F;
int vis[N],vll;

int main() {
    int cas;
    scanf("%d",&cas);
    while (cas--) {
        scanf("%d%d%d",&n,&m,&K);
        memset(graph,0,sizeof(graph));
        F.init();
        int _s = n,_t = n + 1;
        int tot = _t + 1;
        for (int i = 0; i < n; ++ i) {
            F.add_edge(i,_t,1);
        }
        for (int i = 0; i < m; ++ i) {
            int op;
            scanf("%d",&op);
            if (op == 1) {
                int x;
                scanf("%d",&x); x --;
                std::queue<int> que;
                que.push(x);
                vll ++;
                vis[x] = vll;
                while (!que.empty()) {
                    int u = que.front(); que.pop();
                    F.add_edge(tot,u,1);
                    for (int v = 0; v < n; ++ v) {
                        if (graph[u][v] && vis[v] != vll) {
                            vis[v] = vll;
                            que.push(v);
                        }
                    }
                }
                tot ++;
            } else if (op == 2) {
                int a,b;
                scanf("%d%d",&a,&b); a --; b --;
                graph[a][b] = graph[b][a] = true;
            } else {
                int cnt;
                scanf("%d",&cnt);
                while (cnt--) {
                    int a,b;
                    scanf("%d%d",&a,&b); a --; b --;
                    graph[a][b] = graph[b][a] = false;
                }
            }
        }
        int total = 0;
        for (int i = tot - 1; i > _t; -- i) {
            F.add_edge(_s,i,K);
            total += F.dinic(_s,_t);
        }
        printf("%d\n",total);
        std::vector<int> answer;
        for (int i = F.head[_s]; i != -1; i = F.g[i].next) {
            answer.push_back(K - F.g[i].cap);
        }
        for (int i = 0; i < answer.size(); ++ i) {
            if (i) putchar(' ');
            printf("%d",answer[i]);
        }
        puts("");
    }
}
