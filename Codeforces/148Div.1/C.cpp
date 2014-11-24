/* Created Time: Friday, November 22, 2013 PM08:18:38 CST */
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int N = 3333;
const int INF = 0x3f3f3f3f;
int n,head[N],etot,ans;
struct edge {
    int v,next,fuc;
    bool ban;
}g[N<<1];
void add_edge(int u,int v,int fuc) {
    g[etot].v = v; g[etot].fuc = fuc;
    g[etot].next = head[u]; head[u] = etot ++;
}
bool vis[N];
int d[N][2],id,w[2];
void dfs(int u,int fa) {
    vis[u] = true;
    d[u][0] = d[u][1] = 0;
    for (int i = head[u]; i != -1; i = g[i].next) {
        if (g[i].ban) continue;
        int v = g[i].v;
        int c = g[i].fuc;
        if (v==fa) continue;
        dfs(v,u);
        d[u][c] ++;
        d[u][0] += d[v][0];
        d[u][1] += d[v][1];
    }
}
void DFS(int u,int fa,int back) {
    w[id] = min(w[id],back+d[u][1]);
    for (int i = head[u]; i != -1; i = g[i].next) {
        int v = g[i].v;
        int c = g[i].fuc;
        if (g[i].ban) continue;
        if (v==fa) continue;
        DFS(v,u,back+d[u][1]-d[v][1]+(c==1 ? -1 : 1));
    }
}
void work() {
    memset(vis,false,sizeof(vis));
    w[0] = w[1] = INF;
    id = 0;
    for (int i = 1; i <= n; i ++) 
        if (!vis[i]) {
            dfs(i,-1);
            DFS(i,-1,0);
            id ++;
        };
    ans = min(ans,w[0]+w[1]);
}
int main() {
    scanf("%d",&n);
    memset(head,-1,sizeof(head));
    for (int i = 0; i < n-1; i ++) {
        int u,v;
        scanf("%d%d",&u,&v);
        add_edge(u,v,0);
        add_edge(v,u,1);
    }
    if (n==1) {
        puts("0");
        return 0;
    }
    ans = INF;
    for (int i = 0; i < n-1; i ++) {
        g[i<<1].ban = true;
        g[i<<1|1].ban = true;
        work();
        g[i<<1].ban = false;
        g[i<<1|1].ban = false;
    }
    printf("%d\n",ans);
    return 0;
}
